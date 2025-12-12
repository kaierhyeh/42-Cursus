/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:02 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap(t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = -1;
	while (++y < MINIMAP_H)
	{
		x = -1;
		while (++x < MINIMAP_W)
		{
			map_y = y * data->map_boundary / MINIMAP_H;
			map_x = x * (data->map_width - 1) / MINIMAP_W;
			if ((map_x < (int)(ft_strlen(data->map[map_y]) - 1)) \
				&& data->map[map_y][map_x] == '1')
				rc_set_pixel_color(&data->minimap, x, y, 0x212529);
			else if ((map_x < (int)(ft_strlen(data->map[map_y]) - 1)) \
				&& data->map[map_y][map_x] == 'D')
				rc_set_pixel_color(&data->minimap, x, y, 0xFFC300);
			else
				rc_set_pixel_color(&data->minimap, x, y, 0xE9ECEF);
			if ((int)data->ava_pos.x == map_y && (int)data->ava_pos.y == map_x)
				rc_set_pixel_color(&data->minimap, x, y, 0xD62828);
		}
	}
}
