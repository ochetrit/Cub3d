/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclassea <nclassea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:33:56 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/22 20:04:16 by nclassea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	which_first_dir(t_data *data, char dir)
{
	if (dir == 'N')
		data->first_dir = 'N';
	else if (dir == 'S')
		data->first_dir = 'S';
	else if (dir == 'W')
		data->first_dir = 'W';
	else if (dir == 'E')
		data->first_dir = 'E';
}

int	check_map_line(char *line, t_data *data)
{
	while (*line && *line != '\n')
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		while (*line && (*line == '1' || *line == '0'))
			line++;
		if ((*line == 'N' || *line == 'S' || *line == 'W'
				|| *line == 'E') && data->map_start == 0)
		{
			which_first_dir(data, *line);
			data->map_start++;
			line++;
		}
		else if ((*line == 'N' || *line == 'S' || *line == 'W'
				|| *line == 'E') && data->map_start != 0)
			return (ft_putstr_fd(ERR_SPWN, STDERR), false);
		while (*line && (*line == '1' || *line == '0'))
			line++;
		if (!*line || *line == '\n')
			return (true);
		else if (*line != ' ' && *line != '\t')
			return (ft_putstr_fd(ERR_MAP1, STDERR), false);
	}
	return (true);
}

char	*skip_empty_lines(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd, false);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == ' '
				|| line[i] == '\t' || line[i] == '\n'))
			i++;
		if (line[i])
			return (line);
		free(line);
		line = get_next_line(fd, false);
	}
	return (line);
}

int	build_map(t_data *data, t_map *map, int y)
{
	int	x;

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), false);
	data->map[data->map_height] = NULL;
	while (y < data->map_height)
	{
		data->map[y] = malloc(sizeof(char) * (data->map_width + 1));
		if (!data->map[y])
			return (ft_putstr_fd(ERR_MALLOC, STDERR), false);
		x = -1;
		while (++x < data->map_width && map->map[x])
			data->map[y][x] = map->map[x];
		while (x < data->map_width)
		{
			data->map[y][x] = ' ';
			x++;
		}
		data->map[y][x] = '\0';
		map = map->next;
		y++;
	}
	return (true);
}

int	init_map(t_data *data)
{
	t_map	*row;

	data->map_list = malloc(sizeof(t_map *));
	if (!data->map_list)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), false);
	*data->map_list = NULL;
	data->line = skip_empty_lines(data->fd);
	while (data->line)
	{
		if (!check_map_line(data->line, data))
			return (free(data->line), get_next_line(data->fd, true), false);
		row = ft_mapnew(ft_strtrim(data->line, "\n"), data->map_height);
		if (!row)
			return (get_next_line(data->fd, true), free(data->line), false);
		else if (!row->map)
			return (get_next_line(data->fd, true),
				free(row), free(data->line), true);
		ft_mapadd_back(data, data->map_list, row);
		free(data->line);
		data->map_height++;
		data->line = get_next_line(data->fd, false);
	}
	get_next_line(data->fd, true);
	if (data->map_start == 0)
		return (ft_putstr_fd(ERR_SPWN, STDERR), false);
	return (true);
}
