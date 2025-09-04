import speakeasy from 'speakeasy';
import qrcode from 'qrcode';
import bcrypt from 'bcrypt';
import redis from '../redis/redisClient.js';
import authService from '../auth/auth.service.js';
import authUtils from '../auth/auth.utils.js';

export async function twofaRoutes(fastify, options) {
	const { db } = fastify;

	/*** 📌 Route: 2fa/setup ***/
	// Route to setup 2FA for the user.
	// It generates a secret and QR code for the user to scan with an authenticator app.
	// And it returns the otpauth_url and QR code data URL.
	// The secret is temporarily stored until the user verifies it.
	// The QR code is generated from the otpauth_url.
	// The user must scan the QR code and enter the verification code to activate 2FA.
	// The secret is  stored in the database only after successful verification.
	// The QR code is displayed in the frontend for the user to scan.
	fastify.post("/2fa/setup", async (request, reply) => {
		try {
			const userId = request.user.userId;
			// Check if the user exists in the database.
			const user = db.prepare("SELECT * FROM users WHERE id = ?").get(userId);
			if (!user)
				return reply.code(404).send({ success: false, error: "User not found." });

			// Check if 2FA is already enabled for the user.
			if (user.twofa_secret)
				return reply.code(400).send({ success: false, error: "2FA is already enabled." });

			// Prepare the secret for the user using speakeasy.
			const secret = speakeasy.generateSecret({ name: `ft_transcendence:${user.username}` });

			// Generate the otpauth_url for the QR code.
			const qrCode = await qrcode.toDataURL(secret.otpauth_url);

			// Store the secret temporarily in Redis with a 5-minute expiration.
			await redis.setex(`2fa_setup_${userId}`, 300, secret.base32);

			// Store the secret in the database.
			return reply.code(200).send({
				success: true,
				otpauth_url: secret.otpauth_url,
				qrCode		// To be displayed in the frontend.
			});
		} catch (error) {
			fastify.log.error(error, `Error during 2FA setup.`);
			return reply.code(500).send({ success: false, error: "Internal server error during 2FA setup." });
		}
	});

	/*** 📌 Route: 2fa/activate ***/
	// Route to activate 2FA for the user.
	// It verifies the token entered by the user with the secret.\
	// If the token is valid, it stores the secret in the database.
	// If the token is invalid, it returns an error.
	// The user must enter the verification code from the authenticator app.
	fastify.post("/2fa/activate", async (request, reply) => {
		try {
			const userId = request.user.userId;
			const { token } = request.body;

			// Token = the verification code entered by the user.
			const secret = await redis.get(`2fa_setup_${userId}`);
			if (!secret)
				return reply.code(400).send({ success: false, error: "2FA setup expired." });

			// Check if the user exists in the database.
			const isValid = speakeasy.totp.verify({ secret, encoding: 'base32', token });

			if (!isValid)
				return reply.code(400).send({ success: false, error: "Invalid verification code." });
			fastify.log.info(`[2FA] Secret verified for user: ${userId}`);

			// Finally, store the secret in the database.
			db.prepare("UPDATE users SET twofa_secret = ? WHERE id = ?").run(secret, userId);

			// Remove the temporary secret from Redis.
			await redis.del(`2fa_setup_${userId}`);

			return reply.code(200).send({ success: true, message: "2FA successfully activated." });
		} catch (error) {
			fastify.log.error(error, `Error during 2FA activation.`);
			return reply.code(500).send({ success: false, error: "Internal server error during 2FA activation." });
		}
	});

	/*** 📌 Route: 2fa/verify ***/
}