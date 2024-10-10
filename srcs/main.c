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
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->side = 0;
}

void	calc_ray_direction(t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * ray->x / (double)W_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
}

void	init_dda_steps(t_data *data, t_ray *ray)
{
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}



void	run_dda(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->player.pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->player.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->deltadist_y;
	}
}


void	trace_ray_path(t_data *data, t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0 || ray->map_y >= data->map_height)
		{
			// ray outside of map
			hit = 1;
		}
		else if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calc_wall_height(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - data->player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - data->player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(W_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + W_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + W_HEIGHT / 2;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = -1;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_x + ray->wall_dist * ray->dir_x;
	else
		ray->wall_x = data->player.pos_x + ray->wall_dist * ray->dir_y;
	ray->wall_x -= floor(ray->wall_x);
}

void	which_text_dir(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_y > 0)
			data->text.text_index = SO;
		else
			data->text.text_index = NO;
	}
	else
	{
		if (ray->dir_x < 0)
			data->text.text_index = WE;
		else
			data->text.text_index = EA;
	}
}


void	draw_text_column(t_data *data, t_ray *ray, t_text *text)
{
	int color;
	int	y;
	double step;
	double pos;

	which_text_dir(data, ray);
	y = ray->draw_start;
	text->text_x = (int)(ray->wall_x * TEXT_SIZE);
	if (ray->side == 0 && ray->dir_x > 0)
		text->text_x = TEXT_SIZE - text->text_x - 1;
	step = 1.0 * TEXT_SIZE / ray->line_height;
	pos = (ray->draw_start - W_HEIGHT / 2 + ray->line_height / 2) * step;
	while (y < ray->draw_end)
	{
		pos += step;
		color = data->texture_buffer[data->text.text_index][TEXT_SIZE * ((int)pos & (TEXT_SIZE - 1)) + text->text_x];

		if (text->text_index == NO || text->text_index == SO)
			color = (color >> 1) & 0x7F7F7F; // Shading for north and south walls

		if (color > 0)
			data->frame_buffer[y][ray->x] = color; // Draw pixel on screen
		y++;
	}
}

void	display_img(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img, 0, 0);
}

void draw_frame_to_img(t_data *data)
{
	int x, y;

	for (y = 0; y < W_HEIGHT; y++)
	{
		for (x = 0; x < W_WIDTH; x++)
		{
			mlx_pixel_put(data->mlx_ptr, data->win, x, y, data->frame_buffer[y][x]);
		}
	}
}

void	raycasting(t_data *data)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	init_ray(ray);
	ray->x = 0;
	while (ray->x < W_WIDTH)
	{
		calc_ray_direction(ray, &data->player);
		init_dda_steps(data, ray);
		run_dda(data, ray);
		trace_ray_path(data, ray);
		calc_wall_height(data, ray);
		draw_text_column(data, ray, &data->text);
		ray->x++;
	}
}


void	start_game(t_data *data)
{
	setup_player(data);
	raycasting(data);
	draw_frame_to_img(data);
	display_img(data);
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