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

int	check_hitbox(char **map, double x, double y)
{
	if (map[(int)(y + HITBOX)][(int)x] == '1')
		return (false);
	else if (map[(int)(y - HITBOX)][(int)x] == '1')
		return (false);
	else if (map[(int)y][(int)(x + HITBOX)] == '1')
		return (false);
	else if (map[(int)y][(int)(x - HITBOX)] == '1')
		return (false);
	return (true);
}

void	move_forward(t_data *data)
{
	double	check_wall_x;
	double	check_wall_y;

	check_wall_x = data->player.pos_x + data->player.dir_x * (M_S + HITBOX);
	check_wall_y = data->player.pos_y + data->player.dir_y * (M_S + HITBOX);
	if (data->map[(int)(check_wall_y)][(int)(check_wall_x)] != '1' &&
		check_hitbox(data->map, check_wall_x, check_wall_y))
	{
		data->player.pos_x = data->player.pos_x + data->player.dir_x * M_S;
		data->player.pos_y = data->player.pos_y + data->player.dir_y * M_S;;
	}
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_right(t_data *data)
{
	double	check_wall_x;
	double	check_wall_y;

	check_wall_x = data->player.pos_x - data->player.dir_y * (M_S + HITBOX);
	check_wall_y = data->player.pos_y + data->player.dir_x * (M_S + HITBOX);
	if (data->map[(int)check_wall_y][(int)check_wall_x] != '1' &&
		check_hitbox(data->map, check_wall_x, check_wall_y))
	{
		data->player.pos_x = data->player.pos_x - data->player.dir_y * M_S;
		data->player.pos_y = data->player.pos_y + data->player.dir_x * M_S;
	}
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_back(t_data *data)
{
	double	check_wall_x;
	double	check_wall_y;

	check_wall_x = data->player.pos_x - data->player.dir_x * (M_S + HITBOX);
	check_wall_y = data->player.pos_y - data->player.dir_y * (M_S + HITBOX);
	if (data->map[(int)(check_wall_y)][(int)check_wall_x] != '1' &&
		check_hitbox(data->map, check_wall_x, check_wall_y))
	{
		data->player.pos_x = data->player.pos_x - data->player.dir_x * M_S;
		data->player.pos_y = data->player.pos_y - data->player.dir_y * M_S ;
	}
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void	move_left(t_data *data)
{
	double	check_wall_x;
	double	check_wall_y;

	check_wall_x = data->player.pos_x + data->player.dir_y * (M_S + HITBOX);
	check_wall_y = data->player.pos_y - data->player.dir_x * (M_S + HITBOX);
	if (data->map[(int)check_wall_y][(int)check_wall_x] != '1' &&
		check_hitbox(data->map, check_wall_x, check_wall_y))
	{
		data->player.pos_x = data->player.pos_x + data->player.dir_y * M_S;
		data->player.pos_y = data->player.pos_y - data->player.dir_x * M_S;
	}
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void    rotate_left(t_data *data, t_player *player)
{
    double    old_dir_x;
    double    old_plane_x;

    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(R_S) - player->dir_y * sin(-R_S);
    player->dir_y = old_dir_x * sin(-R_S) + player->dir_y * cos(-R_S);
    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(-R_S) - player->plane_y * sin(-R_S);
    player->plane_y = old_plane_x * sin(-R_S) + player->plane_y * cos(-R_S);
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

void    rotate_right(t_data *data, t_player *player)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(R_S) - player->dir_y * sin(R_S);
    player->dir_y = old_dir_x * sin(R_S) + player->dir_y * cos(R_S);
    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(R_S) - player->plane_y * sin(R_S);
    player->plane_y = old_plane_x * sin(R_S) + player->plane_y * cos(R_S);
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
}

int	key_handler(int key, t_data *data)
{
	if (key == ESC)
		end_game(ESC_MSG, data, 8 + W_HEIGHT);
	if (key == W)
		move_forward(data);
	if (key == A)
		move_left(data);
	if (key == S)
		move_back(data);
	if (key == D)
		move_right(data);
	if (key == LEFT_ARROW)
		rotate_left(data, &data->player);
	if (key == RIGHT_ARROW)
		rotate_right(data, &data->player);
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