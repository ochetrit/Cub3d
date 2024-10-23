
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 09:42:34 by ochetrit          #+#    #+#              #
#    Updated: 2024/03/09 17:49:08 by ochetrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
SRCS = srcs/main.c\
	srcs/free.c\
	srcs/init_textures.c\
	srcs/init_colors.c\
	srcs/init_data.c\
	srcs/init_map.c\
	srcs/utils_map.c\
	srcs/parse_map.c\
	srcs/init_game.c\
	srcs/draw.c\
	srcs/raycasting.c\
	srcs/raycasting_utils.c\
	srcs/init_ray.c\
	srcs/moves.c\
	srcs/moves2.c\
	srcs/init_game_utils.c\
	srcs/parsing.c\
	srcs/hooks.c\
	srcs/utils_textures.c

# LIBFT
LIBFT_PATH = ./libft
LIBFT = libft/libft.a

# MLX
LIB_MLX = minilibx-linux/libmlx.a
MLX_A = ./minilibx-linux/libmlx.a
MLX_PATH = minilibx-linux
MLX_FLAG = -lXext -lX11 -lm -lz

OBJS = $(SRCS:.c=.o)
RM = rm -rf

all: minilibx-linux $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@make -C $(MLX_PATH)
	$(RM) $(NAME)
	make all -C $(LIBFT_PATH)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIB_MLX) $(MLX_FLAG) -o $(NAME)

minilibx-linux:
	git clone https://github.com/42Paris/minilibx-linux.git $@

%.o: %.c
	$(CC) -c $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH) 

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re