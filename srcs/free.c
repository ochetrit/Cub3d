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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map **map)
{
	t_map	*current;
	t_map	*next;

	current = *map;
	while (current)
	{
		if (current->map)
			free(current->map);
		if (!current->next)
		{
			free(current);
			break ;
		}
		next = current->next;
		free(current);
		current = next;
	}
	free(map);
}

void	free_data(t_data *data)
{
	if (data->fd > 0)
		close(data->fd);
	if (data->path_no)
		free(data->path_no);
	if (data->path_so)
		free(data->path_so);
	if (data->path_we)
		free(data->path_we);
	if (data->path_ea)
		free(data->path_ea);
	if (data->c_color)
		free(data->c_color);
	if (data->f_color)
		free(data->f_color);
	if (data->map_list)
		free_map(data->map_list);
	if (data->map)
		free_tab(data->map);
	free(data);
}

void	free_buffer(t_data *data, int index)
{
	int	i;

	if (index > 3)
		free(data->texture_buffer[NO]);
	if (index > 4)
		free(data->texture_buffer[SO]);
	if (index > 5)
		free(data->texture_buffer[EA]);
	if (index > 6)
		free(data->texture_buffer[WE]);
	if (index > 2)
		free(data->texture_buffer);
	i = 0;
	while (i < index - 8 && i < W_HEIGHT)
	{
		free(data->frame_buffer[i]);
		i++;
	}
	if (index > 7)
		free(data->frame_buffer);
}

void	end_game(char *msg, t_data *data, int num)
{
	ft_putstr_fd(msg, STDERR); //Sortie d'erreur si le programme ferme normalement ?
	free_buffer(data, num);
	if (num > 1)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (num > 0)
		mlx_destroy_display(data->mlx_ptr);
	if (num > 0)
		free(data->mlx_ptr);
	free_data(data);
	exit(0);
}
