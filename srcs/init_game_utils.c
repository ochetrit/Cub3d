/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:42:01 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/23 15:15:32 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_point	get_screen_size(t_data *data)
{
	t_point	screen_size;

	mlx_get_screen_size(data->mlx_ptr,
		&screen_size.size_x, &screen_size.size_y);
	return (screen_size);
}

void	check_window(t_data *data)
{
	t_point	screen_size;

	screen_size = get_screen_size(data);
	if (W_WIDTH > screen_size.size_x || W_HEIGHT > screen_size.size_y)
		end_game(ERR_MLX, data, 2, STDERR);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		end_game(ERR_MLX, data, 0, STDERR);
	data->win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (!data->win)
		end_game(ERR_MLX, data, 1, STDERR);
	check_window(data);
}

int	red_cross(t_data *data)
{
	end_game(ESC_MSG, data, 8 + W_HEIGHT, STDOUT_FILENO);
	return (0);
}
