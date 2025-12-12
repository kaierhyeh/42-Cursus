/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:11:20 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	check_cub(char *filename)
{
	uint32_t	i;

	i = 0;
	if (!filename)
		return (FALSE);
	while (filename[i] && filename[i] != '.')
		i++;
	if (!ft_strncmp(&filename[i], FILE_EXTENSION, 5))
		return (TRUE);
	ft_printf_fd(ERR, "Bad file extension, expected a .cub file.\n");
	return (FALSE);
}

static int	ini_data(t_data *data, char *file)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map_path = file;
	data->map_fd = open(file, O_RDONLY);
	if (data->map_fd < 0)
	{
		ft_printf_fd(ERR, "Cannot open file.\n");
		return (FALSE);
	}
	data->map_width = 0;
	data->frame = NULL;
	return (SUCCESS);
}

static void	cub_launch(t_data *data)
{
	mlx_loop_hook(data->mlx, rc_rendering, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, &key_events, data);
	mlx_hook(data->window, DestroyNotify, StructureNotifyMask, \
														&cub_clean, data);
	mlx_hook(data->window, ButtonPress, ButtonPressMask, &mouse_press, data);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, &mouse_move, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (check_cub(av[1]) == FALSE)
		return (EXIT_FAILURE);
	if (ini_data(&data, av[1]) == FAILURE)
		return (EXIT_FAILURE);
	if (parse_map(&data) == FAILURE)
		return (EXIT_FAILURE);
	if (initialize_game(&data) == FAILURE)
		return (EXIT_FAILURE);
	cub_launch(&data);
	cub_clean(&data);
	return (0);
}
// Move: WASD
// Turn your head: arrows or mouse
// Open a door: space or left click
// Exit: escape
// Sprite: doors

// uint32_t:
// 	unsigned integer with the fixed length of 32-bit

// initialize_game prepares the first image,
// 	and then cub_launch shows it in a loop.

// cub_launch(t_data *data):
// mlx_loop_hook(data->mlx, rc_rendering, data);
// 	Registers rc_rendering as the function to be called repeatedly
// 	for rendering (or updating) the screen during the main loop.
// mlx_hook(data->window, KeyPress, KeyPressMask, &key_events, data);
// 	Hook to call key_events. KeyPress and KeyPressMask are from X11.h
// mlx_hook(data->window, DestroyNotify, StructureNotifyMask, &cub_clean, data);
// 	Calls cub_clean when the window close event is triggered.
// mlx_hook(data->window, ButtonPress, ButtonPressMask, &mouse_press, data);
// 	Calls mouse_press when a mouse button is pressed.
// mlx_hook(data->window, MotionNotify, PointerMotionMask, &mouse_move, data);
// 	Calls mouse_move when the mouse moves within the window.
// mlx_loop(data->mlx);
// 	Starts the event loop that keeps the program running.