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
# define ERR_COLOR2 "Error\nInvalid comas in color\n"
# define ERR_SPWN "Error\nInvalid spawn\n"
# define ERR_MAP1 "Error\nInvalid item\n"
# define ERR_WALL "Error\nInvalid wall\n"
# define TEXT_LOAD_FAILED "Error\nTexture loading failed\n"
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define C 4
# define F 5
# define EMPTY 6
# define ERROR 7
# define END 8
# define W_TITLE "Cub3D"
# define W_WIDTH 640
# define W_HEIGHT 480
// # define NORTH 0
// # define SOUTH 1
// # define WEST 2
// # define EAST 3

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

typedef struct img
{
	void	*img;
	char	*addr; // adresse pixels de l img
	int		bbp; // bits per pixel
	int		line_length; // longueur de ligne en octets
	int		endian; // Endianness de l'image (0 pour big endian, 1 pour little endian)
}				t_img;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}				t_player;

typedef	struct s_map
{
	char	*map;
	int		x_start;
	int		y_current;
	struct	s_map	*next;
}				t_map;


typedef struct	s_data
{
	int	fd;
	char	*line;
	char	first_dir;
	t_map	**map_list;
	char	**map;
	int		map_height;
	int		map_width;
	int		map_start;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	void	*mlx_ptr;
	void	*win;
	int		**texture_buffer;
	t_point	screen_size;
	t_player	player;
	unsigned char	*c_color;
	unsigned int		c_color_key;
	unsigned char	*f_color;
	unsigned int		f_color_key;
}				t_data;


//// 1. Check that the file respects the rules ////

// FREE
void	free_data(t_data *data);
void	end_game(char *msg, t_data *data, int num);


// INIT GAME
void	init_game(t_data *data);
t_data			*init_data(char *file);
int				find_path_and_color(t_data *data);
int				init_map(t_data *data);
int				build_map(t_data *data, t_map *map, int y);
int				parse_map(char **map, int height, int width);
unsigned char	*build_color(char *line, int *key);
void			init_color_key(t_data *data);
void			ft_mapadd_back(t_data *data, t_map **head, t_map *new);
t_map			*ft_mapnew(char *content, int map_height);
t_map			*ft_maplast(t_map *lst);
