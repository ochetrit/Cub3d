/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:07:09 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/21 15:38:49 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void set_pix(t_img *img, int x, int y, int color)
{
	int pix;

	pix = y * (img->line_length / 4) + x;
	img->addr[pix] = color;
}

static void	my_mlx_put_pix(t_data *data, t_img *img, int x, int y)
{
	if (data->frame_buffer[y][x] > 0)
		set_pix(img, x, y, data->frame_buffer[y][x]);
	else if (y < W_HEIGHT / 2)
		set_pix(img, x, y, data->c_color_key);
	else if (y < W_HEIGHT - 1)
		set_pix(img, x, y, data->f_color_key);
}

void	img_create(t_data *data, t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bbp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!img->img)
		end_game(ERR_MLX, data, 2);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bbp, &img->line_length, &img->endian);
	return ;
}


void	draw_frame_to_img(t_data *data, t_img *img)
{
	int x;
	int y;

	y = 0;
	img->img = NULL;
	img_create(data, img);
	
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			my_mlx_put_pix(data, img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
}
