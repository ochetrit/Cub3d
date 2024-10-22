/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:14:16 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/22 19:49:57 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_text(t_text *text)
{
	text->text_index = 0;
	text->text_x = 0;
	text->text_y = 0;
	text->text_width = 0;
	text->pos = 0;
	text->step = 0;
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
