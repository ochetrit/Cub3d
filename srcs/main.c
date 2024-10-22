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
			if (is_player(data->map[y][x]))
			{
				player->pos_x = x + 0.5;// + 0.5
				player->pos_y = y + 0.5;// + 0.5
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

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * M_S;
	new_y = data->player.pos_y + data->player.dir_y * M_S;
	if (data->map[(int)(new_y)][(int)(new_x)] != '1')
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	printf("x: %f, y: %f\n", data->player.pos_x, data->player.pos_y);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * M_S;
	new_y = data->player.pos_y + data->player.dir_x * M_S;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_back(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * M_S;
	new_y = data->player.pos_y - data->player.dir_y * M_S;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * M_S;
	new_y = data->player.pos_y - data->player.dir_x * M_S;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

int	key_handler(int key, t_data *data)
{
	if (key == ESC)
		end_game(ESC_MSG, data, 7 + W_HEIGHT);
	if (key == W)
		move_forward(data);
	if (key == A)
		move_left(data);
	if (key == S)
		move_back(data);
	if (key == D)
		move_right(data);
	// if (key == 123)
	// if (key == 124)
	return (0);
}


void	start_game(t_data *data)
{
	set_player(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
	// add hooks
	mlx_key_hook(data->win, key_handler, data);
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

// 	set_text(text);
// 	which_text_dir(text, ray);
// 	text->text_x = (int)(ray->wall_x * TEXT_SIZE);
// 	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
// 		text->text_x = TEXT_SIZE - text->text_x - 1;
// 	step = (1.0 * TEXT_SIZE) / ray->line_height;
// 	pos = (ray->draw_start - W_HEIGHT / 2 + ray->line_height / 2) * step;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		text->text_y = (int)pos & (TEXT_SIZE - 1);
// 		pos += step;
// 		color = data->texture_buffer[text->text_index][TEXT_SIZE * text->text_y + text->text_x];
// 		if (color > 0)
// 			data->frame_buffer[y][x] = color;
// 		y++;
// 	}
// }