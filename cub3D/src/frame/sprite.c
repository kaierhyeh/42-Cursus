/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:51:42 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	play_sprite_forward(t_data *data, int map_x, int map_y)
{
	t_frame	*sprite;
	t_frame	door;

	sprite = data->frame;
	door.img = data->texture->img[D];
	door.addr = data->texture->addr[D];
	door.height = data->texture->height[D];
	door.width = data->texture->width[D];
	while (sprite)
	{
		data->texture->img[D] = sprite->img;
		data->texture->addr[D] = sprite->addr;
		data->texture->height[D] = sprite->height;
		data->texture->width[D] = sprite->width;
		rc_rendering(data);
		mlx_do_sync(data->mlx);
		sprite = sprite->next;
		usleep(100000);
	}
	data->map[map_x][map_y] = 'O';
	data->texture->img[D] = door.img;
	data->texture->addr[D] = door.addr;
	data->texture->height[D] = door.height;
	data->texture->width[D] = door.width;
}

void	play_sprite_backward(t_data *data, int map_x, int map_y)
{
	t_frame	*sprite;
	t_frame	door;

	sprite = frame_lstlast(data->frame);
	door.img = data->texture->img[D];
	door.addr = data->texture->addr[D];
	door.height = data->texture->height[D];
	door.width = data->texture->width[D];
	data->map[map_x][map_y] = 'D';
	while (sprite)
	{
		data->texture->img[D] = sprite->img;
		data->texture->addr[D] = sprite->addr;
		data->texture->height[D] = sprite->height;
		data->texture->width[D] = sprite->width;
		rc_rendering(data);
		mlx_do_sync(data->mlx);
		sprite = sprite->before;
		usleep(100000);
	}
	data->texture->img[D] = door.img;
	data->texture->addr[D] = door.addr;
	data->texture->height[D] = door.height;
	data->texture->width[D] = door.width;
}
