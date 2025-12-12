/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:38:13 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:24 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3D.h"

# define TEXTURE_NB 7
# define TEXTURE_PATH 5

typedef enum e_bool		t_bool;
typedef struct s_data	t_data;
typedef enum e_texture
{
	N = 0,
	S = 1,
	E = 2,
	W = 3,
	D = 4,
}	t_texture;

typedef struct s_texture_data
{
	void	*img[TEXTURE_PATH];
	int		height[TEXTURE_PATH];
	int		width[TEXTURE_PATH];
	char	*path[TEXTURE_PATH];
	char	*addr[TEXTURE_PATH];
	int		floor;
	int		ceiling;
	int		nb;
}	t_texture_data;

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	FAILURE_ERR,
}	t_parse_status;

//	parser
int				parse_map(t_data *data);
void			cub_fill_whitespace(char **map);
char			**build_map(t_data *data, char *line);
t_parse_status	check_invalid_char(char **map);
t_parse_status	find_start(int coordinate[], char **map);

//	get_texture
t_texture_data	*get_texture_data(t_data *data, char **line);
int				add_data_buff(char *line, t_texture_data *texture, \
														t_texture type);
int				cub_atoi(char *line, t_texture_data *texture, int *color);
int				check_texture_path(char **path);

#endif