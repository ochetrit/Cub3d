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

void setup_player(t_data *data)
{
	if (data->first_dir == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else if (data->first_dir == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	else if (data->first_dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
	else if (data->first_dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
}

void	calc_ray_direction(t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * ray->x / (double)W_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
}

void	raycasting(t_data *data)
{
	t_ray *ray;

	int	x;
	x = 0;
	ray = malloc(sizeof(t_ray));
	init_ray(ray);
	while (ray->x < W_WIDTH)
	{
		ray->x = 0;
		calc_ray_direction(ray, &data->player);
		// init_dda_steps(data);
		// run_dda(data);
		// calc_line_height(data);
		// drat_text_column(data);
		ray->x++;
	}
}


void	start_game(t_data *data)
{
	setup_player(data);
	// raycasting
	// draw img
	// add hooks
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