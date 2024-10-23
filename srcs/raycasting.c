/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:12:09 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/23 18:36:51 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		ray->sidedist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->player.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->deltadist_y;
	}
}

void	trace_ray_path(t_data *data, t_ray *ray)
{
	int	hit;

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
			break ;
		if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calc_wall_height(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(W_HEIGHT / ray->wall_dist);
	ray->draw_start = (-ray->line_height + W_HEIGHT) / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height + W_HEIGHT) / 2;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	set_text_pix(t_data *data, t_ray *ray, t_text *text, int x)
{
	int		color;
	int		y;

	set_text(text);
	which_text_dir(text, ray);
	y = ray->draw_start;
	text->text_x = (int)(ray->wall_x * TEXT_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		text->text_x = TEXT_SIZE - text->text_x - 1;
	text->step = 1.0 * TEXT_SIZE / ray->line_height;
	text->pos = (ray->draw_start - W_HEIGHT / 2
			+ ray->line_height / 2) * text->step;
	while (y < ray->draw_end)
	{
		color = data->texture_buffer[text->text_index][TEXT_SIZE
			* ((int)text->pos & (TEXT_SIZE - 1)) + text->text_x];
		text->pos += text->step;
		if (text->text_index == NO || text->text_index == SO)
			color = (color >> 1) & 0x7F7F7F;
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
		set_ray_direction(data, &data->ray, &data->player, x);
		set_dda(data, &data->ray);
		trace_ray_path(data, &data->ray);
		calc_wall_height(data, &data->ray);
		set_text_pix(data, &data->ray, &data->text, x);
		x++;
	}
}
