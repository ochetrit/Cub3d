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

void	start_game(t_data *data)
{
	set_player(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, key_release, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = parsing(ac, av);
	if (!data)
		return (1);
	init_game(data);
	start_game(data);
	return (free_data(data), 0);
}
