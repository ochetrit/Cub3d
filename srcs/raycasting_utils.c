/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:16:30 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/22 19:53:05 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_ray_direction(t_data *data, t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)W_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	which_text_dir(t_text *text, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			text->text_index = NO;
		else
			text->text_index = SO;
	}
	else
	{
		if (ray->dir_y < 0)
			text->text_index = WE;
		else
			text->text_index = EA;
	}
}

int	outside_map(t_data *data, int x, int y)
{
	if (x < 0.25 || y < 0.25 || x > data->map_width - 1.25
		|| y > data->map_height - 1.25)
		return (1);
	return (0);
}

void	set_player(t_data *data)
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
