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

t_point	get_screen_size(t_data *data)
{
	t_point screen_size;

	mlx_get_screen_size(data->mlx_ptr, &screen_size.size_x, &screen_size.size_y);
	return (screen_size);
}

void	check_window(t_data *data)
{
	t_point screen_size;
	screen_size = get_screen_size(data);
	if (W_WIDTH > screen_size.size_x || W_HEIGHT > screen_size.size_y)
		end_game(ERR_MLX, data, 2);

}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		end_game(ERR_MLX, data, 2);
	data->win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (!data->win)
		end_game(ERR_MLX, data, 2);
	check_window(data);
}

int	red_cross(t_data *data)
{
	end_game(ESC_MSG, data, 2);
	return (0);
}


void	load_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_texture));
	if (!data->textures)
		end_game(ERR_MALLOC, data, 2);
	data->textures[WEST] = xpm_to_img(data, data->texture_path.west);
	data->textures[EAST] = xpm_to_img(data, data->texture_path.east);
	data->textures[NORTH] = xpm_to_img(data, data->texture_path.north);
	data->textures[SOUTH] = xpm_to_img(data, data->texture_path.south);
}


void	init_game(t_data *data)
{
	init_window(data);
	load_textures(data);
	// set_up_sprites(data);
	// set_up_player(data);
	mlx_hook(data->win, DESTROY_NOTIF, NO_EVENT_MASK, red_cross, data);
	mlx_loop(data->mlx_ptr);
	// init_img(data);
	// dans init img ajouter to Optimising Performance
	// - img.img  = mlx_new_img;
	// - img.addr = get_data_addr
}
