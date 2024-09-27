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

# define STDERR STDERR_FILENO
# define ERR_ARG "Error\nInvalid argument\n"
# define ERR_FILE "Error\nInvalid file\n"
# define ERR_MALLOC "Error\nMalloc failed\n"
# define ERR_CHAR "Error\nI need an invalid char\n"
# define ERR_COLOR "Error\nInvalid color\n"
# define ERR_COLOR2 "Error\nInvalid comas in color\n"
# define ERR_SPWN "Error\nInvalid spawn\n"
# define ERR_MAP1 "Error\nInvalid item\n"
# define ERR_WALL "Error\nInvalid wall\n"
# define EMPTY 0
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define C 5
# define F 6
# define ERROR 7
# define END 8

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
	t_map	**map;
	int		map_height;
	int		map_width;
	int		map_start;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	unsigned char	*c_color;
	unsigned int		c_color_key;
	unsigned char	*f_color;
	unsigned int		f_color_key;
}				t_data;


//// 1. Check that the file respects the rules ////
t_data			*init_data(char *file);
int				find_path_and_color(t_data *data);
int				init_map(t_data *data);
unsigned char	*build_color(char *line, int *key);
void			init_color_key(t_data *data);
void			free_data(t_data *data);
void			ft_mapadd_back(t_map **head, t_map *new);
t_map			*ft_mapnew(char *content, int map_height);
t_map			*ft_maplast(t_map *lst);