/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:05:27 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/23 17:55:57 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
# define TEXT_SIZE 64
# define MINIMAP_SCALE 0.1
# define RED 0
# define GREEN 1
# define M_S 0.015
# define R_S 0.02

/*key*/
# define DESTROY_NOTIF 17
# define NO_EVENT_MASK 0
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define HITBOX 0.1
# define KEYPRESS 2
# define KEYRELEASE 3

// MSG
# define ESC_MSG "\n\nQuitting the game. Thank you for playing!\n"
# define STDERR STDERR_FILENO
# define ERR_ARG "Error\nInvalid argument\n"
# define ERR_FORM "Error\nInvalid file syntax\n"
# define ERR_KEY "Error\nInvalid texture key\n"
# define ERR_FILE "Error\nInvalid file\n"
# define ERR_NB_KEY "Error\nDuplicates key\n"
# define ERR_MALLOC "Error\nMalloc failed\n"
# define ERR_NB_COLOR "Error\nInvalid number of color\n"
# define ERR_CHAR "Error\nI need a valid char\n"
# define ERR_COLOR "Error\nInvalid color\n"
# define ERR_MLX "Error\nMlx failed\n"
# define ERR_COLOR2 "Error\nInvalid comas in color\n"
# define ERR_SPWN "Error\nInvalid spawn\n"
# define ERR_NB_PLAYER "Error\nInvalid number of player\n"
# define ERR_MAP1 "Error\nInvalid item\n"
# define ERR_WALL "Error\nInvalid wall\n"
# define TEXT_LOAD_FAILED "Error\nTexture loading failed\n"
# define ERR_MLX_NEW_IMG "Error\nMlx new image failed\n"

typedef struct s_point
{
	int				size_x;
	int				size_y;
}					t_point;

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_keys;

typedef struct img
{
	void			*img;
	int				*addr;
	int				bbp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_text
{
	int				text_index;
	int				text_x;
	int				text_y;
	int				text_width;
	double			step;
	double			pos;
}					t_text;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			wall_dist;
	double			wall_x;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_map
{
	char			*map;
	int				x_start;
	int				y_current;
	struct s_map	*next;
}					t_map;

typedef struct s_data
{
	int				fd;
	char			*line;
	char			first_dir;
	t_map			**map_list;
	char			**map;
	int				map_height;
	int				map_width;
	int				map_start;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	void			*mlx_ptr;
	void			*win;
	int				**texture_buffer;
	int				**frame_buffer;
	int				**color_buffer;
	t_point			screen_size;
	t_ray			ray;
	t_player		player;
	t_text			text;
	t_img			img;
	t_keys			keys;
	unsigned char	*c_color;
	unsigned int	c_color_key;
	unsigned char	*f_color;
	unsigned int	f_color_key;
}					t_data;

//// 1. Check that the file respects the rules ////

// FREE
void				free_data(t_data *data);
void				end_game(char *msg, t_data *data, int num, int fd);

// INIT GAME
void				init_game(t_data *data);
t_data				*init_data(char *file);
int					find_path_and_color(t_data *data);
int					init_map(t_data *data);
int					build_map(t_data *data, t_map *map, int y);
int					parse_map(char **map, int height, int width);
unsigned char		*build_color(char *line, int *key);
void				init_color_key(t_data *data);
void				ft_mapadd_back(t_data *data, t_map **head, t_map *new);
t_map				*ft_mapnew(char *content, int map_height);
t_map				*ft_maplast(t_map *lst);
void				init_window(t_data *data);
int					red_cross(t_data *data);
int					is_player(char c);
int					len_path(char *line);
int					check_if_exists(int *key, t_data *data);
t_data				*parsing(int ac, char **av);

// DRAW
void				draw_frame_to_img(t_data *data, t_img *img);
void				set_pixel(t_data *data, t_img *img, int x, int y);
void				init_frame_buffer(t_data *data);

// RAYCASTING
void				raycasting(t_data *data);
void				set_ray_direction(t_data *data, t_ray *ray,
						t_player *player, int x);
void				which_text_dir(t_text *text, t_ray *ray);
int					outside_map(t_data *data, int x, int y);
void				set_player(t_data *data);

// INIT RAY
void				set_text(t_text *text);
void				init_ray(t_ray *ray);

// MOVES
int					game_loop(t_data *data);
int					check_hitbox(char **map, double x, double y);
void				rotate_right(t_player *player);
void				rotate_left(t_player *player);

// HOOKS
int					key_release(int key, t_data *data);
int					key_press(int key, t_data *data);

#endif