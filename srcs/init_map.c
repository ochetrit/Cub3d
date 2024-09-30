/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:33:56 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/30 15:54:02 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_line(char *line, t_data *data)
{
	while (*line && *line != '\n')
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		while (*line && (*line == '1' || *line == '0'))
			line++;
		if ((*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E') && data->map_start == 0)
		{
			data->map_start++;
			line++;
		}
		else if ((*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E') && data->map_start != 0)
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
		while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
			i++;
		if (line[i])
			return (line);
		free(line);
		line = get_next_line(fd, false);
	}
	return (line);
}

int	parse_map(t_map	*lst, int height)
{
	t_map	*next;
	int		i;

	i = 0;
	next = ft_maplast(lst);
	while (lst->map[i] && (lst->map[i] == '1' || lst->map[i] == ' '))
		i++;
	if (lst->map[i])
		return (ft_putstr_fd(ERR_WALL, STDERR), false);
	i = 0;
	while (next->map[i] && (next->map[i] == '1' || next->map[i] == ' '))
		i++;
	if (next->map[i])
		return (ft_putstr_fd(ERR_WALL, STDERR), false);
	height--;
	return (true);
}

int	build_map(t_data *data, t_map *map)
{
	int	x;
	int	y;
	
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), false);
	data->map[data->map_height] = NULL;
	y = 0;
	printf("map_width: %d\n", data->map_width);
	printf("map_height: %d\n", data->map_height);
	while (y < data->map_height)
	{
		data->map[y] = malloc(sizeof(char) * (data->map_width + 1));
		if (!data->map[y])
			return (ft_putstr_fd(ERR_MALLOC, STDERR), false);
		x = -1;
		while (++x < data->map_width && map->map[x])
			data->map[y][x] = map->map[x];
		while (++x < data->map_width)
			data->map[y][x] = ' ';
		data->map[y][x] = '\0';
		printf("%s\n", data->map[y]);
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
			return (get_next_line(data->fd, true), free(row), free(data->line), true);
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
