/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:12:10 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_texture	get_wall_dir(t_data *data)
{
	if (data->ray_dir.door == TRUE)
		return (D);
	if (data->side == 0)
	{
		if (data->ray_dir.x < 0)
			return (N);
		else
			return (S);
	}
	else
	{
		if (data->ray_dir.y < 0)
			return (E);
		else
			return (W);
	}
}

static void	get_x(int *w_pos, t_data *data, double ray_d)
{
	double	wall_hit;
	int		dir;

	dir = get_wall_dir(data);
	if (data->side == 0)
		wall_hit = data->ava_pos.y + ray_d * data->ray_dir.y;
	else
		wall_hit = data->ava_pos.x + ray_d * data->ray_dir.x;
	wall_hit -= floor(wall_hit);
	w_pos[0] = (int)(wall_hit * data->texture->width[dir]);
	if (w_pos[0] >= data->texture->width[dir])
		w_pos[0] = data->texture->width[dir] - 1;
}

static void	get_y(int *w_pos, t_data *data, int wall_height, int y)
{
	int	y_scaled;
	int	dir;

	dir = get_wall_dir(data);
	y_scaled = y * 256 - HEIGHT * 128 + wall_height * 128;
	w_pos[1] = ((y_scaled * data->texture->height[dir]) / wall_height) / 256;
	if (w_pos[1] < 0)
		w_pos[1] = 0;
	if (w_pos[1] >= data->texture->height[dir])
		w_pos[1] = data->texture->height[dir] - 1;
}

void	rc_render_wall(t_data *data, int x, int y, double ray_d)
{
	t_wall			w_data;
	t_texture_data	*texture;
	int				color;
	int				dir;
	int				color_index;

	dir = get_wall_dir(data);
	texture = data->texture;
	w_data.height = (int)(HEIGHT / ray_d);
	w_data.boundary[0] = (HEIGHT - w_data.height) / 2;
	if (w_data.boundary[0] < 0)
		w_data.boundary[0] = 0;
	w_data.boundary[1] = (HEIGHT + w_data.height) / 2;
	if (w_data.boundary[1] >= HEIGHT)
		w_data.boundary[1] = HEIGHT - 1;
	get_x(w_data.w_pos, data, ray_d);
	get_y(w_data.w_pos, data, w_data.height, y);
	color_index = w_data.w_pos[1] * texture->width[dir] + w_data.w_pos[0];
	color = ((uint32_t *)texture->addr[dir])[color_index];
	rc_set_pixel_color(&data->image, x, y, color);
}
