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

int	form_arg(char *arg)
{
	char	*str;

	str = ft_strchr(arg, '.');
	if (!str || ft_strcmp(str, ".cub"))
		return (false);
	else if (str != ft_strrchr(arg, '.'))
		return (false);
	return (true);
}

t_data	*parsing(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || !form_arg(av[1]))
		return (ft_putstr_fd(ERR_ARG, STDERR), NULL);
	data = init_data(av[1]);
	if (!data)
		return (NULL);
	if (!find_path_and_color(data))
		return (free_data(data), NULL);
	init_color_key(data);
	if (!init_map(data))
		return (free_data(data), NULL);
	else if (!build_map(data, *data->map_list, 0))
		return (free_data(data), NULL);
	else if (!parse_map(data->map, data->map_height, data->map_width))
		return (free_data(data), NULL);
	return (data);
}

void	init_player_data_test(t_data *data)
{
	data->player.pos_x = 22;
	data->player.pos_y = 12;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}


void	start_game(t_data *data)
{
	// faire une fonction pour initialiser les données du joueur avec t_Data et char direction
	init_player_data_test(data);

	// raycasting
	// draw img
	mlx_loop(data->mlx_ptr);
}

int main(int ac, char **av)
{
	t_data	*data;

	data = parsing(ac, av);
	if (!data)
		return (1);
	init_game(data);
	start_game(data);
	return (free_data(data), 0);
} 