/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:07:09 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/18 19:29:23 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void set_pix(t_img *img, int x, int y, int color)
{
	int pix;

	pix = y * (img->line_length / 4) + x;
	printf("pix = %d\n", pix);
	img->addr[pix] = color;
}

static void	my_mlx_put_pix(t_data *data, t_img *img, int x, int y)
{
	// if (data->color_buffer[y][x] > 0)
	// set_pix(img, x, y, data->color_buffer[y][x]);
	if (data->frame_buffer[y][x] > 0)
		set_pix(img, x, y, data->frame_buffer[y][x]);
	
	
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

void set_pixel_direct(t_img *img, int x, int y, int color)
{
    int pix;

    // Calcul de l'index du pixel
    pix = (y * img->line_length / 4) + x;

    // Assigner la couleur au pixel (en supposant que l'addr est un tableau d'entiers)
    img->addr[pix] = color;
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
			// int color = data->color_buffer[y][x];
			// // printf("color[%d][%d] = %d\n", y, x, color);
			// if (color > 0)
			// {
			// 	int pix = y * (img->line_length / 4) + x;
			// 	img->addr[pix] = color;
			// }
			// else
			// {
			// 	int pix = y * (img->line_length / 4) + x;
			// 	img->addr[pix] = 0xFFFFF;
			// }
			my_mlx_put_pix(data, img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
}
