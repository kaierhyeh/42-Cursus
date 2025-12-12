/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:16:09 by kyeh              #+#    #+#             */
/*   Updated: 2025/12/12 11:12:01 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//	libraries
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <math.h>

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"

# include "parser.h"
# include "frame.h"
# include "vector.h"

# define SUCCESS 0
# define FAILURE 1

# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ERR STDERR_FILENO
# define NAME "cub3d"

//	screen
# define WIDTH 1280
# define HEIGHT 720
# define FOV 90
# define ROT_STEP 1.5f
# define MOUSE_ROT_STEP 1.0f
# define MOVE_STEP 0.1f
# define MINIMAP_W 200
# define MINIMAP_H 200
# define MINIMAP_X 15
# define MINIMAP_Y 505
# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define FILE_EXTENSION ".cub"
# define FRAME_SCRIPT "./assets/animations/door_frame.txt"

typedef enum e_texture			t_texture;
typedef struct s_texture_data	t_texture_data;
typedef struct s_image			t_image;
typedef struct s_wall
{
	int	height;
	int	boundary[2];
	int	w_pos[2];
}	t_wall;

typedef enum e_key
{
	ARROW_RIGHT = 65363,
	ARROW_LEFT = 65361,
	ARROW_UP = 65362,
	ARROW_DOWN = 65364,
	ESC_KEY = 65307,
	SPACE_KEY = 32,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	R_KEY = 114,
	M1 = 65307,
	P_KEY = 112,
}	t_key;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_rot
{
	CLOCK,
	CCLOCK,
}	t_rot;

typedef enum e_move
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
}	t_move;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	char			*map_path;
	int				map_fd;
	size_t			map_boundary;
	size_t			map_width;
	char			**map;
	void			*mlx;
	void			*window;
	int				pause;
	t_image			image;
	t_image			minimap;
	t_texture_data	*texture;
	t_frame			*frame;
	t_wall			w_data;
	t_vec			ava_pos;
	t_vec			ava_dir;
	t_vec			ava_cam;
	t_vec			ray_dir;
	int				side;
}	t_data;

int		cub_clean(t_data *data);
void	cub_free_texture(t_texture_data *texture);
void	cub_free_texture_mlx(t_texture_data *texture, void *mlx);
int		initialize_game(t_data *data);
int		key_events(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		mouse_press(int button, int x, int y, t_data *data);
void	interact_door(t_data *data);
void	move_check(t_vec *step, t_data *data, int add_or_min);

// /* * * * * * * * * * * color.c * * * * * * * * * * */
int		create_trgb(int t, int r, int g, int b);

// /* * * * * * * * * * * RC Rendering * * * * * * * * * * */
int		rc_rendering(t_data *data);
void	rc_ray_ini(t_vec *d, t_vec *pos, t_vec *dir, t_vec *unit_d);
int		rc_update_pos(t_vec *d, t_vec *unit_d, t_vec *pos, t_vec *dir);
void	rc_draw_stripe_column(t_data *data, int x, double ray_d);
void	rc_render_wall(t_data *data, int x, int y, double ray_d);
void	rc_set_pixel_color(t_image *image, int x, int y, int color);

// /* * * * * * * * * * * Minimap * * * * * * * * * * */
void	put_minimap(t_data *data);

// /* * * * * * * * * * * Sprite * * * * * * * * * * */
void	play_sprite_forward(t_data *data, int map_x, int map_y);
void	play_sprite_backward(t_data *data, int map_x, int map_y);

#endif
// TEXTURE_NB:
// 	used to count the data
// 	(the rest is the map itself)