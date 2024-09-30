/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:05:27 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/12 11:26:01 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define STDERR STDERR_FILENO
# define ERR_ARG "Error\nInvalid argument\n"
# define ERR_FILE "Error\nInvalid file\n"
# define ERR_MALLOC "Error\nMalloc failed\n"
# define ERR_CHAR "Error\nI need an invalid char\n"
# define ERR_COLOR "Error\nInvalid color\n"
# define ERR_MLX "Error\nMlx failed\n"
# define EMPTY 0
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define C 5
# define F 6
# define ERROR 7
# define END 8
# define W_TITLE "Cub3D"
# define W_WIDTH 640
# define W_HEIGHT 480
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

/*key*/
# define DESTROY_NOTIF 17
# define NO_EVENT_MASK 0

// MSG
# define ESC_MSG "\n\nQuitting the game. Thank you for playing!"

typedef struct	s_point
{
	int	size_x;
	int	size_y;
}				t_point;

typedef struct texture
{
	char *north;
	char *south;
	char *west;
	char *east;
}				t_texture;


typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}				t_player;

typedef struct	s_data
{
	int	fd;
	char	*line;
	char	**map;
	int		map_height;
	int		map_width;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	**c_color;
	char	**f_color;
	void	*mlx_ptr;
	void	*win;
	int		**textures;
	t_texture	texture_path;
	t_point	screen_size;
	t_player player;
}				t_data;


//// 1. Check that the file respects the rules ////
t_data	*init_data(char *file);
int	find_path_and_color(t_data *data);
char	**build_color(char *line);

// FREE
void	free_data(t_data *data);
void	end_game(char *msg, t_data *data, int num);


// INIT MLX
void	init_mlx_data(t_data *data);