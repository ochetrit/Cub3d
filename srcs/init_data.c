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

#include "../includes/cub3d.h"

t_data	*init_data(char *file)
{
	t_data	*data;

	printf("je passe ici\n");
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), NULL);
	data->fd = open(file, O_RDONLY);
	printf("OHHHOHOHOHO\n");
	if (data->fd < 0)
	{
		free(data);
		return (ft_putstr_fd(ERR_FILE, STDERR), NULL);
	}
	data->line = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->path_ea = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	return (data);
}
