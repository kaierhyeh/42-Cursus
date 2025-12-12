/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:23:01 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	pause_game(t_data *data)
{
	if (data->pause == TRUE)
		data->pause = FALSE;
	else
		data->pause = TRUE;
}

static void	move_camera(t_data *data, t_rot dir)
{
	if (dir == CLOCK)
	{
		vec_rotate(&data->ava_cam, ROT_STEP * -1);
		vec_rotate(&data->ava_dir, ROT_STEP * -1);
	}
	else
	{
		vec_rotate(&data->ava_cam, ROT_STEP);
		vec_rotate(&data->ava_dir, ROT_STEP);
	}
}

static void	move_player(t_data *data, t_move dir)
{
	t_vec	step;

	if (dir == FORWARD)
	{
		vec_copy_scale(&step, &data->ava_dir, MOVE_STEP);
		move_check(&step, data, 0);
	}
	else if (dir == BACKWARD)
	{
		vec_copy_scale(&step, &data->ava_dir, MOVE_STEP);
		move_check(&step, data, 1);
	}
	else if (dir == RIGHT)
	{
		vec_copy_scale(&step, &data->ava_cam, MOVE_STEP);
		move_check(&step, data, 0);
	}
	else if (dir == LEFT)
	{
		vec_copy_scale(&step, &data->ava_cam, MOVE_STEP);
		move_check(&step, data, 1);
	}
}

static void	turn_around(t_data *data)
{
	vec_mirror(&data->ava_cam);
	vec_mirror(&data->ava_dir);
}

int	key_events(int keycode, t_data *data)
{
	if (keycode == P_KEY)
		pause_game(data);
	else if (keycode == ARROW_RIGHT && data->pause == FALSE)
		move_camera(data, CLOCK);
	else if (keycode == ARROW_LEFT && data->pause == FALSE)
		move_camera(data, CCLOCK);
	else if (keycode == W_KEY && data->pause == FALSE)
		move_player(data, FORWARD);
	else if (keycode == S_KEY && data->pause == FALSE)
		move_player(data, BACKWARD);
	else if (keycode == A_KEY && data->pause == FALSE)
		move_player(data, LEFT);
	else if (keycode == D_KEY && data->pause == FALSE)
		move_player(data, RIGHT);
	else if (keycode == R_KEY && data->pause == FALSE)
		turn_around(data);
	else if (keycode == SPACE_KEY && data->pause == FALSE)
		interact_door(data);
	else if (keycode == ESC_KEY)
		cub_clean(data);
	return (SUCCESS);
}
