/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:08:13 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rc_set_pixel_color(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	rc_draw_stripe_column(t_data *data, int x, double ray_d)
{
	int	y;
	int	wall_height;

	wall_height = (int)(HEIGHT / ray_d);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < (HEIGHT - wall_height) / 2)
			rc_set_pixel_color(&data->image, x, y, data->texture->ceiling);
		else if (y > (HEIGHT + wall_height) / 2)
			rc_set_pixel_color(&data->image, x, y, data->texture->floor);
		else
			rc_render_wall(data, x, y, ray_d);
	}
}
