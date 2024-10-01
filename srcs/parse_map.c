/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:17:02 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/01 17:39:13 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_boarder(char **map)
{
	int	x;
	int y;

	y = 0;
	x = 0;
	while (map[y][x] && (map[y][x] == '1' || map[y][x] == ' '))
		x++;
	if (map[y][x])
		return (ft_putstr_fd(ERR_WALL, STDERR), false);
	x--;
	while (map[y] && (map[y][x] == '1' || map[y][x] == ' '))
		y++;
	if (map[y])
		return (ft_putstr_fd(ERR_WALL, STDERR), false);
	y--;
	while (x >= 0 && (map[y][x] == '1' || map[y][x] == ' '))
		x--;
	if (x >= 0)
		return (ft_putstr_fd(ERR_WALL, STDERR), false); 
	x++;
	while (y >= 0 && (map[y][x] == '1' || map[y][x] == ' '))
		y--;
	if (y >= 0)
		return (ft_putstr_fd(ERR_WALL, STDERR), false);
	return (true);
}

int	parse_map(char **map, int height, int width)
{
	int	x;
	int	y;
	
	y = 0;
	if (!check_boarder(map))
		return (false);
	y = 1;
	while (y < height - 1)
	{
		x = 1;
		while (x < width - 1)
		{
			if (map[y][x] == '0')
			{
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ' || map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
					return (ft_putstr_fd(ERR_WALL, STDERR), false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
