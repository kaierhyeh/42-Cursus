/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:49:29 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_texture_addr(t_texture_data *t)
{
	int	bpp;
	int	ll;
	int	endian;

	t->addr[N] = mlx_get_data_addr(t->img[N], &bpp, &ll, &endian);
	t->addr[S] = mlx_get_data_addr(t->img[S], &bpp, &ll, &endian);
	t->addr[E] = mlx_get_data_addr(t->img[E], &bpp, &ll, &endian);
	t->addr[W] = mlx_get_data_addr(t->img[W], &bpp, &ll, &endian);
	t->addr[D] = mlx_get_data_addr(t->img[D], &bpp, &ll, &endian);
}

static int	ini_frame(char *line, t_data *data, t_frame *f)
{
	char	*path;

	path = ft_strtrim(line, "\n");
	if (!path)
		return (FAILURE);
	f->img = mlx_xpm_file_to_image(data->mlx, path, &f->width, &f->height);
	if (!f->img)
		return (free(path), FAILURE);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->ll, &f->endian);
	frame_lstadd_back(&data->frame, f);
	free(path);
	return (SUCCESS);
}

static int	load_frame(t_data *data)
{
	t_frame	*f;
	int		frame_fd;
	char	*line;

	frame_fd = open(FRAME_SCRIPT, O_RDONLY);
	if (frame_fd < 0)
		return (FAILURE);
	line = get_next_line(frame_fd);
	if (!line)
		return (FAILURE);
	while (line)
	{
		f = frame_lstnew();
		if (!f)
			return (close(frame_fd), FAILURE);
		if (ini_frame(line, data, f) == FAILURE)
			return (free(line), close(frame_fd), free(f), FAILURE);
		free(line);
		line = get_next_line(frame_fd);
	}
	close(frame_fd);
	return (SUCCESS);
}

static int	load_assets(t_data *data)
{
	t_texture_data	*t;
	char			**p;
	void			*m;

	t = data->texture;
	p = t->path;
	m = data->mlx;
	t->img[N] = mlx_xpm_file_to_image(m, p[N], &t->width[N], &t->height[N]);
	t->img[S] = mlx_xpm_file_to_image(m, p[S], &t->width[S], &t->height[S]);
	t->img[E] = mlx_xpm_file_to_image(m, p[E], &t->width[E], &t->height[E]);
	t->img[W] = mlx_xpm_file_to_image(m, p[W], &t->width[W], &t->height[W]);
	t->img[D] = mlx_xpm_file_to_image(m, p[D], &t->width[D], &t->height[D]);
	if (!t->img[N] || !t->img[S] || !t->img[E] || !t->img[W] || !t->img[D])
		return (FAILURE);
	get_texture_addr(t);
	if (load_frame(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	initialize_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (FAILURE);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, NAME);
	if (!data->window)
	{
		ft_printf_fd(ERR, "Error when opening window.\n");
		cub_clean(data);
		return (FAILURE);
	}
	if (load_assets(data) == FAILURE)
	{
		ft_printf_fd(ERR, "Error when loading assets.\n");
		cub_clean(data);
		return (FAILURE);
	}
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_length, &data->image.endian);
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_W, MINIMAP_H);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img,
			&data->minimap.bpp, &data->minimap.line_length,
			&data->minimap.endian);
	return (SUCCESS);
}
// bpp	= bits per pixel
// ll	= line length