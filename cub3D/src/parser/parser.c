/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:37:33 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ini_player_direction(t_data *data, uint32_t x, uint32_t y)
{
	if (data->map[x][y] == 'N')
	{
		vec_ini(&data->ava_dir, -1.0f, 0.0f);
		vec_ini(&data->ava_cam, 0.0f, tan(FOV / 2));
	}
	else if (data->map[x][y] == 'S')
	{
		vec_ini(&data->ava_dir, 1.0f, 0.0f);
		vec_ini(&data->ava_cam, 0.0f, tan(FOV / 2) * -1);
	}
	else if (data->map[x][y] == 'E')
	{
		vec_ini(&data->ava_dir, 0.0f, 1.0f);
		vec_ini(&data->ava_cam, tan(FOV / 2), 0.0f);
	}
	else if (data->map[x][y] == 'W')
	{
		vec_ini(&data->ava_dir, 0.0f, -1.0f);
		vec_ini(&data->ava_cam, tan(FOV / 2) * -1, 0.0f);
	}
	vec_ini(&data->ava_pos, (double)x, (double)y);
}

static t_parse_status	check_wall(char **map, uint32_t x, uint32_t y, \
									size_t boundary)
{
	if (x == boundary || y >= ft_strlen(map[x]))
		return (MAP_ERR);
	else if (map[x][y] == 'F' || map[x][y] == 'C' || map[x][y] == '1')
		return (MAP_OK);
	else if (x == 0 || !map[x])
		return (MAP_ERR);
	else if (y == 0 || !map[x][y] || map[x][y] == '\n')
		return (MAP_ERR);
	if (map[x][y] == 'D')
		map[x][y] = 'C';
	else
		map[x][y] = 'F';
	if (check_wall(map, x - 1, y, boundary) == MAP_ERR)
		return (MAP_ERR);
	if (check_wall(map, x + 1, y, boundary) == MAP_ERR)
		return (MAP_ERR);
	if (check_wall(map, x, y - 1, boundary) == MAP_ERR)
		return (MAP_ERR);
	if (check_wall(map, x, y + 1, boundary) == MAP_ERR)
		return (MAP_ERR);
	if (map[x][y] == 'C')
		map[x][y] = 'D';
	return (MAP_OK);
}

static t_parse_status	verify_map(char **map, t_data *data)
{
	int	start[2];

	start[0] = -1;
	start[1] = -1;
	if (check_invalid_char(map) == MAP_ERR)
		return (MAP_ERR);
	cub_fill_whitespace(map);
	if (find_start(start, map) == MAP_ERR)
		return (MAP_ERR);
	ini_player_direction(data, start[0], start[1]);
	if (check_wall(map, start[0], start[1], data->map_boundary) == MAP_ERR)
		return (MAP_ERR);
	return (MAP_OK);
}

int	parse_map(t_data *data)
{
	char	*line;

	line = get_next_line(data->map_fd);
	if (!line)
		return (FAILURE);
	data->texture = get_texture_data(data, &line);
	if (!data->texture)
	{
		if (line)
			free(line);
		close(data->map_fd);
		ft_printf_fd(ERR, "Error.\n");
		return (FAILURE);
	}
	data->map = build_map(data, line);
	close(data->map_fd);
	if (!data->map)
		return (cub_free_texture_mlx(data->texture, data->mlx), FAILURE);
	if (verify_map(data->map, data) == MAP_ERR)
	{
		ft_printf_fd(ERR, "Error.\n");
		cub_free_texture_mlx(data->texture, data->mlx);
		return (free_array(data->map), FAILURE);
	}
	return (SUCCESS);
}

// void	print_parsed_map(t_data *data)
// {
// 	int	i = 0;

// 	printf("texture:\n");
// 	while (i < 4)
// 	{
// 		printf("path %d is %s\n", i, data->texture->path[i]);
// 		printf("address %d is %s\n", i, data->texture->addr[i]);
// 		i++;
// 	}
// 	printf("text floor is %d\n", data->texture->floor);
// 	printf("text ceiling is %d\n", data->texture->ceiling);
// 	i = 0;
// 	while (data->map[i])
// 	{
// 		printf("%s", data->map[i]);
// 		i++;
// 	}
// }

// ini_player_direction:
// 	N, S, E, W: facing direction;
// ava_cam:
// 	This vector could represent the direction perpendicular to ava_dir,
// 	used to calculate the camera's projection or view plane.
// 	The tangent of half the field of view (FOV)
// 	helps determine how wide the camera's vision is on the screen.