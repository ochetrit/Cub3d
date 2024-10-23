/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:46:03 by nclassea          #+#    #+#             */
/*   Updated: 2024/10/23 15:13:11 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		end_game(ESC_MSG, data, 8 + W_HEIGHT, STDOUT_FILENO);
	if (key == W)
		data->keys.w = 1;
	if (key == A)
		data->keys.a = 1;
	if (key == S)
		data->keys.s = 1;
	if (key == D)
		data->keys.d = 1;
	if (key == LEFT_ARROW)
		data->keys.left = 1;
	if (key == RIGHT_ARROW)
		data->keys.right = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == W)
		data->keys.w = 0;
	if (key == A)
		data->keys.a = 0;
	if (key == S)
		data->keys.s = 0;
	if (key == D)
		data->keys.d = 0;
	if (key == LEFT_ARROW)
		data->keys.left = 0;
	if (key == RIGHT_ARROW)
		data->keys.right = 0;
	return (0);
}
