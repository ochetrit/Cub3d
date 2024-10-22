/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:53:42 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/22 17:08:01 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

}

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(R_S) - player->dir_y * sin(-R_S);
	player->dir_y = old_dir_x * sin(-R_S) + player->dir_y * cos(-R_S);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-R_S) - player->plane_y * sin(-R_S);
	player->plane_y = old_plane_x * sin(-R_S) + player->plane_y * cos(-R_S);

}

void	rotate_right(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(R_S) - player->dir_y * sin(R_S);
	player->dir_y = old_dir_x * sin(R_S) + player->dir_y * cos(R_S);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(R_S) - player->plane_y * sin(R_S);
	player->plane_y = old_plane_x * sin(R_S) + player->plane_y * cos(R_S);
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
		rotate_left(&data->player);
	if (key == RIGHT_ARROW)
		rotate_right(&data->player);
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
	return (0);
}