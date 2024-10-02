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

// t_img xpm_to_img(t_data *data, char *path)
// {
// 	t_img img;
// 	int	size[2];

// 	img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &size[0], &size[1]);
// 	if (!img.img)
// 		end_game(ERR_MLX, data, 2);
// 	img.addr = mlx_get_data_addr(img.img, &img.bbp, &img.line_length, &img.endian);
// 	if (!img.addr)
// 		end_game(ERR_MLX, data, 2);
// 	return (img);
// }


int	*xpm_to_img(t_data *data, char *path)
{
	int	*buf;
	int	size[2];
	
	size[0] = 0;
	size[1] = 0;
	buf = mlx_xpm_file_to_image(data->mlx_ptr, path, &size[0], &size[1]);
	if (!buf)
		end_game(ERR_MLX, data, 2);
	return (buf);
}

void	load_textures(t_data *data)
{
	int i;
	data->texture_buffer = ft_calloc(4, sizeof * data->texture_buffer);
	if (!data->texture_buffer)
		end_game(ERR_MALLOC, data, 2);
	i = 0;
	// while (i < 4)
	// {
	// 	data->texture_buffer[i] = ft_calloc(1, sizeof * data->texture_buffer[i]);
	// 	if (!data->texture_buffer[i])
	// 		end_game(ERR_MALLOC, data, 2);
	// 	i++;
	// }
	data->texture_buffer[NO] = xpm_to_img(data, data->path_no);
	data->texture_buffer[SO] = xpm_to_img(data, data->path_so);
	data->texture_buffer[EA] = xpm_to_img(data, data->path_ea);
	data->texture_buffer[WE] = xpm_to_img(data, data->path_we);
}

void	test_display_test(t_data *data)
{
	if (data->texture_buffer[NO])
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win, data->texture_buffer[NO], 0, 0);
	}
	else
	{
		printf("NO texture not loaded\n");
	}
}

void	init_game(t_data *data)
{
	init_window(data);
	load_textures(data);
	test_display_test(data);
	// set_up_sprites(data);
	set_up_player(data);
	mlx_hook(data->win, DESTROY_NOTIF, NO_EVENT_MASK, red_cross, data);
	mlx_loop(data->mlx_ptr);
	// init_img(data);
	// dans init img ajouter to Optimising Performance
	// - img.img  = mlx_new_img;
	// - img.addr = get_data_addr
}
