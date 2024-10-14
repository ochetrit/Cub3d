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

t_point	get_screen_size(t_data *data)
{
	t_point screen_size;

	mlx_get_screen_size(data->mlx_ptr, &screen_size.size_x, &screen_size.size_y);
	return (screen_size);
}

void	check_window(t_data *data)
{
	t_point screen_size;
	screen_size = get_screen_size(data);
	if (W_WIDTH > screen_size.size_x || W_HEIGHT > screen_size.size_y)
		end_game(ERR_MLX, data, 2);

}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		end_game(ERR_MLX, data, 2);
	data->win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (!data->win)
		end_game(ERR_MLX, data, 2);
	check_window(data);
}

int	red_cross(t_data *data)
{
	end_game(ESC_MSG, data, 2);
	return (0);
}

void set_img(t_data *data, t_img *img, char *path)
{
	int size_img;

	size_img = 64;
	img->addr = 0;
	img->bbp = 0;
	img->img = 0;
	img->endian = 0;
	img->line_length = 0;
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &size_img, &size_img);
	if (!img->img)
		end_game(TEXT_LOAD_FAILED, data, 2);
	if (!img->img)
		end_game(TEXT_LOAD_FAILED, data, 2);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bbp, &img->line_length, &img->endian);
	if (!img->addr)
		end_game(TEXT_LOAD_FAILED, data, 2);
	return ;
}

int	*load_text_img(t_data *data, char *path)
{
	t_img img;
	int *buf;
	int x;
	int y;

	set_img(data, &img, path);
	buf = ft_calloc(1, sizeof * buf * (64 * 64));
	if (!buf)
		end_game(ERR_MLX, data, 2);
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			buf[y * 64 + x] = img.addr[y * 64 + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, img.img);
	return (buf);
}

void	init_textures(t_data *data)
{
	data->texture_buffer = ft_calloc(4, sizeof * data->texture_buffer);
	if (!data->texture_buffer)
		end_game(ERR_MALLOC, data, 2);
	data->texture_buffer[NO] = load_text_img(data, data->path_no);
	data->texture_buffer[SO] = load_text_img(data, data->path_so);
	data->texture_buffer[EA] = load_text_img(data, data->path_ea);
	data->texture_buffer[WE] = load_text_img(data, data->path_we);
	printf(" pix = %x\n", data->texture_buffer[SO][0]);
}

void init_frame_buffer(t_data *data)
{
	int i;

	i = 0;
	data->frame_buffer = malloc(sizeof(int *) * W_HEIGHT);
	if (!data->frame_buffer)
		end_game(ERR_MALLOC, data, 2);

	while (i < W_HEIGHT)
	{
		data->frame_buffer[i] = malloc(sizeof(int) * W_WIDTH);
		if (!data->frame_buffer[i])
			end_game(ERR_MALLOC, data, 2);
		i++;
	}
}


void	init_game(t_data *data)
{
	init_window(data);
	init_textures(data);
	init_frame_buffer(data);
	mlx_hook(data->win, DESTROY_NOTIF, NO_EVENT_MASK, red_cross, data);
	
}
