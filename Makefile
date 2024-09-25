
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

SRCS = srcs/main.c srcs/free.c srcs/init_textures.c srcs/init_colors

LIB_MLX = minilibx-linux/libmlx.a

OBJS = $(SRCS:.c=.o) ./libft/libft.a

NAME = cub3D

CC = cc

RM = rm -rf

FLAGS = -Wall -Wextra -g3 -O3

LDFLAGS = -L./libft -lft

all: $(LIB_MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB_MLX) -lXext -lX11 -lm -lz

minilibx-linux:
	git clone https://github.com/42Paris/minilibx-linux.git $@

$(LIB_MLX): minilibx-linux
			cd minilibx-linux && make

./libft/libft.a: FORCE
	@$(MAKE) -C libft/

%.o: %.c
	$(CC) -c $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean

fclean: clean
	$(RM) $(NAME) minilibx-linux
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re FORCE
