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

int is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void find_player_pos(t_data *data, t_player *player)
{
	int x;
	int y;
	int n;

	y = 0;
	n = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			printf("%c", data->map[y][x]);
			if (is_player(data->map[y][x]))
			{
				player->pos_x = x;// + 0.5
				player->pos_y = y;// + 0.5
				n++;
			}
			if (n > 1)
			{
				printf("TOO MANY PLAYERS\n");
				end_game(ERR_SPWN, data, 2);
			}
			x++;
		}
		y++;
	}
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
	find_player_pos(data, &data->player);
	return (data);
}

void	setup_player2(t_data *data)
{
	if (data->first_dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
	else if (data->first_dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else
		return ;
}

void setup_player(t_data *data)
{
	if (data->first_dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->first_dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else
		return ;
}

void	init_player_pos(t_data *data)
{
	setup_player(data);
	setup_player2(data);
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

void	calc_ray_direction(t_data *data, t_ray *ray, t_player *player, int x)
{
	(void)data;
	ray->camera_x = 2 * x / (double)W_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

// void	init_dda_steps(t_data *data, t_ray *ray)
// {
// 	ray->map_x = (int)data->player.pos_x;
// 	ray->map_y = (int)data->player.pos_y;
// 	ray->deltadist_x = fabs(1 / ray->dir_x);
// 	ray->deltadist_y = fabs(1 / ray->dir_y);
// }



void	set_dda(t_data *data, t_ray *ray)
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

int	outside_map(t_data *data, int x, int y)
{
	if (x < 0.25 || y < 0.25 || x > data->map_width - 1.25 || y > data->map_height - 1.25)
		return (1);
	return (0);
}

void draw_line(t_data *data, t_ray *ray, int x, int y)
{
		if (ray->side == 0)
		{
			printf("HERE\n");
			data->color_buffer[y][x] = 0xFF0000; // Rouge
		}
		else
		{
			printf("HERE2222\n");
			data->color_buffer[y][x] = 0x00FF00; // Vert
		}
}



void	trace_ray_path(t_data *data, t_ray *ray)
{
	int hit;

	hit = 0;
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
		if (outside_map(data, ray->map_x, ray->map_y))
		{
			printf("OUTSIDE MAP\n");
			break ;
		}
		else if (data->map[ray->map_y][ray->map_x] == '1')
		{
			hit = 1;
		}
		// draw_line(data, ray, ray->map_x, ray->map_y);
	}
}
	// if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0 || ray->map_y >= data->map_height)
	// {
	// 	// ray outside of map
	// 	hit = 1;
	// }

void	calc_wall_height(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(W_HEIGHT / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + W_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + W_HEIGHT / 2;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	which_text_dir(t_text *text, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_y < 0)
			text->text_index = NO;
		else
			text->text_index = SO;
	}
	else
	{
		if (ray->dir_x < 0)
			text->text_index = WE;
		else
			text->text_index = EA;
	}
}

 
void	set_text(t_text *text)
{
	text->text_index = 0;
	text->text_x = 0;
	text->text_y = 0;
	text->text_width = 0;
}

void	draw_text_column(t_data *data, t_ray *ray, t_text *text, int x)
{
	int color;
	int	y;
	double step;
	double pos;

	set_text(text);
	which_text_dir(text, ray);
	text->text_x = (int)(ray->wall_x * TEXT_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		text->text_x = TEXT_SIZE - text->text_x - 1;
	step = (1.0 * TEXT_SIZE) / ray->line_height;
	pos = (ray->draw_start - W_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		text->text_y = (int)pos & (TEXT_SIZE - 1);
		pos += step;
		color = data->texture_buffer[text->text_index][TEXT_SIZE * text->text_y + text->text_x];
		if (color > 0)
			data->frame_buffer[y][x] = color;
		y++;
	}
}


void	raycasting(t_data *data)
{
	int	x;

	x = 0;
	while (x < W_WIDTH)
	{
		init_ray(&data->ray);
		calc_ray_direction(data, &data->ray, &data->player, x);
		// init_dda_steps(data, &data->ray);
		set_dda(data, &data->ray);
		trace_ray_path(data, &data->ray);
		calc_wall_height(data, &data->ray);
		draw_text_column(data, &data->ray, &data->text, x);
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		printf("ray->map_x = %d\n", data->ray.map_x);
		printf("ray->map_y = %d\n", data->ray.map_y);
		printf("ray->side = %d\n", data->ray.side);
		printf("ray->sidedist_x = %f\n", data->ray.sidedist_x);
		printf("ray->sidedist_y = %f\n", data->ray.sidedist_y);
		printf("ray->deltadist_x = %f\n", data->ray.deltadist_x);
		printf("ray->deltadist_y = %f\n", data->ray.deltadist_y);
		printf("ray->draw_start = %d\n", data->ray.draw_start);
		printf("ray->draw_end = %d\n", data->ray.draw_end);
		printf("ray->line_height = %d\n", data->ray.line_height);
		printf("ray->wall_dist = %f\n", data->ray.wall_dist);
		printf("ray->wall_x = %f\n", data->ray.wall_x);
		printf("ray->camera_x = %f\n", data->ray.camera_x);
		x++;
	}
	// print all color from color_buffer
	// int y = 0;
	// while (y < W_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < W_WIDTH)
	// 	{
	// 		printf("data->color_buffer[%d][%d] = %d\n", y, x, data->color_buffer[y][x]);
	// 		x++;
	// 	}
	// 	y++;
	// }
}


void	start_game(t_data *data)
{
	init_player_pos(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
	// mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img, 0, 0);
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



// void	draw_text_column(t_data *data, t_ray *ray, t_text *text, int x)
// {
// 	int color;
// 	int	y;
// 	double step;
// 	double pos;

// 	which_text_dir(data, ray);
// 	y = ray->draw_start;
// 	text->text_x = (int)(ray->wall_x * TEXT_SIZE);
// 	if (ray->side == 0 && ray->dir_x > 0)
// 		text->text_x = TEXT_SIZE - text->text_x - 1;
// 	step = 1.0 * TEXT_SIZE / ray->line_height;
// 	pos = (ray->draw_start - W_HEIGHT / 2 + ray->line_height / 2) * step;
// 	while (y < ray->draw_end)
// 	{
// 		color = data->texture_buffer[data->text.text_index][TEXT_SIZE * ((int)pos & (TEXT_SIZE - 1)) + text->text_x];
// 		pos += step;

// 		if (text->text_index == NO || text->text_index == SO)
// 			color = (color >> 1) & 0x7F7F7F; // Shading for north and south walls

// 		if (color > 0)
// 			data->frame_buffer[y][x] = color; // Draw pixel on screen
// 		y++;
// 	}
// }