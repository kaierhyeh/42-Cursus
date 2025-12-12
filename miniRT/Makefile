# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:27:51 by kyeh              #+#    #+#              #
#    Updated: 2025/12/12 11:10:46 by kyeh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME	= cub3d

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address

# Source files
SRC_PAR	=	$(addprefix parser/, \
				parser.c				parser_utils.c		build_map.c \
				get_texture.c			get_texture_utils.c)
SRC_F	=	$(addprefix frame/, \
				frame_lst.c				sprite.c)
SRC_RC	=	$(addprefix ray_casting/, \
				ray_casting.c			render_color.c		render_wall.c)
SRC_VEC	=	$(addprefix vector/, \
				vector_arithmetics.c	vector_plane.c		vector_cos_scale.c)
SRC_MAP	=	$(addprefix minimap/, \
				put_minimap.c)
SRC_EVE	=	$(addprefix events/, \
				key_events.c			mouse_door.c		wall_collision.c)
SRC_MAIN	=	main.c cub_free.c color.c initialize_game.c

SRC_FILES	=	$(SRC_MAIN) $(SRC_PAR) $(SRC_F) $(SRC_RC) $(SRC_VEC) $(SRC_MAP) $(SRC_EVE)
SRC_PATH	=	src/
SRC			=	$(addprefix $(SRC_PATH), $(SRC_FILES))

HEADER		=	include/

# Object files
OBJ_FILES	=	$(SRC_FILES:%.c=%.o)
OBJ_PATH	=	obj/
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_FILES))

RM			=	rm -rf

LIBFT_PATH	=	libft/
LIBFT		=	$(addprefix $(LIBFT_PATH), libft.a)

MLX			= minilibx-linux
MLXFLAGS	= -L $(MLX) -lmlx -lXext -lX11 -lXext -lm -lz -Ofast
#######################################################
# Colors
DEFAULT		= \e[0;39m
BLACK		= \e[0;30m
WHITE		= \e[0;97m
WHITE_BOLD	= \e[1;97m
GREY		= \e[0;37m
GREY_DARK	= \e[0;90m
GREY_ITALIC	= \e[3;90m
RED			= \e[0;31m
RED_BOLD	= \e[1;31m
RED_LIGHT	= \e[0;31;110m
RED_FLASH	= \e[0;31;5;110m
PINK		= \e[0;38;5;198m
PINK_BOLD	= \e[1;95m
PINK_LIGHT	= \e[0;38;5;200m
ORANGE_ITALIC= \e[3;91m
YELLOW		= \e[0;33m
YELLOW_BOLD	= \e[1;33m
GREEN		= \e[1;32;111m
GREEN_BOLD	= \e[1;32m
GREEN_LIGHT	= \e[0;38;5;121m
BLUE_BOLD	= \e[1;34m
BLUE_LIGHT	= \e[0;38;5;123m
BLUE_GREY	= \e[1;38;5;110m
SKY			= \e[0;36m
SKY_BOLD	= \e[1;36m
CYAN_LIGHT	= \e[0;96m
NOCOLOR		= \e[0m
RESET_LINE	= \e[2K\r
#######################################################
all: $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(MLXFLAGS) -lreadline -o  $@
	@printf "	\033[2K\r$(DARK_BLUE)cub3d\t: $(LIGHT_GREEN)Updated\n\033[0m"

bonus:	$(NAME)

$(MLX):
	@$(MAKE) -C $(MLX) all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)/cub3D.h Makefile
	@mkdir -p $(dir $@)
	@printf "$(RESET_LINE)$(RED_FLASH)Compiling...	$(GREY)$<$(SKY) $(NOCOLOR)"
	@gcc $(CFLAGS) -I $(HEADER) -I libft/include -I $(MLX) -c $< -o $@

clean: cleanlib cleanmlx
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/.	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/..	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/...	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/.	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/..	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting cub3d srcs/...	$(GREY)"
	@sleep 0.1
	@$(RM) $(OBJ_PATH)
	@printf "$(RESET_LINE)$(RED_FLASH)Deleted successfully!\n$(NOCOLOR)"

cleanlib:
	@$(MAKE) -C $(LIBFT_PATH) clean

cleanmlx:
	@$(MAKE) -C $(MLX) clean

fclean: fcleanlib clean
	@$(RM) $(NAME)

fcleanlib:
	@$(MAKE) -C $(LIBFT_PATH) fclean

re:	fclean all

.PHONY: all bonus minilibx-linux clean cleanlib cleanmlx fclean fcleanlib re
# minilibx-linux:
# 	! -d checks if a directory doesn't exist

# @ suppresses the command being printed to the terminal when it's executed.
# all, clean,... are phony targets, not actual files, used as conditions after make command
# when "make", it builds only the first target in the makefile
#
# -c means compile without linking, and thus renders .o files
# $< represents the dependency to build the target
# $@ represents the target name itself
# -o means output
# $@ specifies that the output should have the same name as the target file
# ar rcs = ar rc + ranlib