/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:36:53 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/22 19:53:42 by nclassea         ###   ########.fr       */
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
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(R_S) - player->dir_y * sin(R_S);
	player->dir_y = old_dir_x * sin(R_S) + player->dir_y * cos(R_S);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(R_S) - player->plane_y * sin(R_S);
	player->plane_y = old_plane_x * sin(R_S) + player->plane_y * cos(R_S);
}
