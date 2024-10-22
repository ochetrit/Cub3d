/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:53:42 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/22 19:47:47 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		data->player.pos_y = data->player.pos_y + data->player.dir_y * M_S;
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

int	game_loop(t_data *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.s)
		move_back(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(&data->player);
	if (data->keys.right)
		rotate_right(&data->player);
	init_ray(&data->ray);
	init_frame_buffer(data);
	raycasting(data);
	draw_frame_to_img(data, &data->img);
	return (0);
}
