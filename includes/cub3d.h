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
# define EMPTY 0
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define C 5
# define F 6
# define ERROR 7
# define END 8

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
}				t_data;


//// 1. Check that the file respects the rules ////
t_data	*init_data(char *file);
int	find_path_and_color(t_data *data);