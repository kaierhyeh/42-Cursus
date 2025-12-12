/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:31:48 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_data *data)
{
	if (data->pause == TRUE)
		return (0);
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (SUCCESS);
	if (x >= WIDTH / 2)
	{
		vec_rotate(&data->ava_cam, MOUSE_ROT_STEP * -1);
		vec_rotate(&data->ava_dir, MOUSE_ROT_STEP * -1);
	}
	else
	{
		vec_rotate(&data->ava_cam, MOUSE_ROT_STEP);
		vec_rotate(&data->ava_dir, MOUSE_ROT_STEP);
	}
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	return (SUCCESS);
}

static double	get_door_distance(t_vec *ray, t_data *data)
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
			return (1);
		else if (data->map[(int)ray_pos.x][(int)ray_pos.y] == 'D' \
				|| data->map[(int)ray_pos.x][(int)ray_pos.y] == 'O')
			break ;
	}
	if (data->side == 1)
		return ((ray_d.y - unit_d.y) * vec_cos(ray, &data->ava_dir));
	else
		return ((ray_d.x - unit_d.x) * vec_cos(ray, &data->ava_dir));
}

static void	change_door_state(t_data *data, t_vec *ava_ray)
{
	int		door_x;
	int		door_y;

	door_x = data->ava_pos.x + ava_ray->x;
	door_y = data->ava_pos.y + ava_ray->y;
	if (data->map[door_x][door_y] == 'D')
		play_sprite_forward(data, door_x, door_y);
	else if (data->map[door_x][door_y] == 'O')
		play_sprite_backward(data, door_x, door_y);
}

void	interact_door(t_data *data)
{
	t_vec	ava_ray;
	double	d;

	ava_ray.x = data->ava_dir.x;
	ava_ray.y = data->ava_dir.y;
	d = get_door_distance(&ava_ray, data);
	if (d > 0.5)
		return ;
	change_door_state(data, &ava_ray);
	return ;
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		interact_door(data);
	return (SUCCESS);
}
