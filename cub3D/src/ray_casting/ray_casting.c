/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:21:41 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rc_ray_ini(t_vec *d, t_vec *pos, t_vec *dir, t_vec *unit_d)
{
	if (dir->x < 0)
		d->x = (pos->x - (int)pos->x) * unit_d->x;
	else
		d->x = ((int)pos->x + 1.0 - pos->x) * unit_d->x;
	if (dir->y < 0)
		d->y = (pos->y - (int)pos->y) * unit_d->y;
	else
		d->y = ((int)pos->y + 1.0 - pos->y) * unit_d->y;
}

int	rc_update_pos(t_vec *d, t_vec *unit_d, t_vec *pos, t_vec *dir)
{
	if (d->x < d->y)
	{
		d->x += unit_d->x;
		if (dir->x < 0)
			pos->x -= 1;
		else
			pos->x += 1;
		return (0);
	}
	else
	{
		d->y += unit_d->y;
		if (dir->y < 0)
			pos->y -= 1;
		else
			pos->y += 1;
		return (1);
	}
}

static double	rc_ray_distance(t_vec *ray, t_data *data)
{
	t_vec	ray_pos;
	t_vec	unit_d;
	t_vec	ray_d;

	ray->door = FALSE;
	vec_ini(&ray_pos, data->ava_pos.x, data->ava_pos.y);
	unit_d.x = sqrt(1 + ((ray->y * ray->y) / (ray->x * ray->x)));
	unit_d.y = sqrt(1 + ((ray->x * ray->x) / (ray->y * ray->y)));
	rc_ray_ini(&ray_d, &ray_pos, ray, &unit_d);
	while (1)
	{
		data->side = rc_update_pos(&ray_d, &unit_d, &ray_pos, ray);
		if (data->map[(int)ray_pos.x][(int)ray_pos.y] == '1')
			break ;
		if (data->map[(int)ray_pos.x][(int)ray_pos.y] == 'D')
		{
			ray->door = TRUE;
			break ;
		}
	}
	if (data->side == 1)
		return ((ray_d.y - unit_d.y) * vec_cos(ray, &data->ava_dir));
	else
		return ((ray_d.x - unit_d.x) * vec_cos(ray, &data->ava_dir));
}

int	rc_rendering(t_data *data)
{
	int		x;
	double	cam_x;
	double	ray_d;

	mlx_clear_window(data->mlx, data->window);
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		data->ray_dir.x = data->ava_dir.x + data->ava_cam.x * cam_x;
		data->ray_dir.y = data->ava_dir.y + data->ava_cam.y * cam_x;
		ray_d = rc_ray_distance(&data->ray_dir, data);
		rc_draw_stripe_column(data, x, ray_d);
	}
	put_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->window, data->minimap.img,
		MINIMAP_X, MINIMAP_Y);
	return (SUCCESS);
}
// d for distance

// Casting:
// 	https://lodev.org/cgtutor/raycasting3.html

// rc_ray_distance - unit_d: step size