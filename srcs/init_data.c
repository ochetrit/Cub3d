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

void	init_point(t_point *point)
{
	point->size_x = 0;
	point->size_y = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_datas(t_data *data)
{
	data->line = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->map_start = 0;
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->path_ea = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	data->mlx_ptr = NULL;
	data->win = NULL;
	data->texture_buffer = NULL;
	data->frame_buffer = NULL;
	data->map_list = NULL;
}

t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), NULL);
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		free(data);
		return (ft_putstr_fd(ERR_FILE, STDERR), NULL);
	}
	init_datas(data);
	init_point(&data->screen_size);
	init_player(&data->player);
	init_keys(&data->keys);
	return (data);
}
