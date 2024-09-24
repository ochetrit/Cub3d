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

t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		free(data);
		return (ft_putstr_fd(ERR_FILE, STDERR), NULL);
	}
	data->line = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->path_ea = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	return (data);
}

int	which_one(char *line)
{
	if (!line)
		return (END);
	else if (!*line)
		return (EMPTY);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line)
		return (EMPTY);
	else if (ft_strncmp(line, "NO", 2))
		return (NO);
	else if (ft_strncmp(line, "SO", 2))
		return (SO);
	else if (ft_strncmp(line, "WE", 2))
		return (WE);
	else if (ft_strncmp(line, "EA", 2))
		return (EA);
	else if (ft_strncmp(line, "C", 1))
		return (C);
	else if (ft_strncmp(line, "F", 1))
		return (F);
	else
		return (ERROR);
}

char	*str_extract(char *line, int key)
{
	char	*str;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	line++;
	if (key < C)
		line++;
	key = 0;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	while (line[key] && line[key] != ' ' && line[key] != '\t')
		key++;
	str = malloc(sizeof(char) * (key + 1));
	if (!str)
		return (NULL);
	key = 0;
	while (line[key] && line[key] != ' ' && line[key] != '\t')
	{
		str[key] = line[key];
		key++;
	}
	str[key] = '\0';
	return (str);
}

int	find_path_and_color(t_data *data)
{
	int	key;

	data->line = get_next_line(data->fd);
	while (data->line)
	{
		key = which_one(data->line);
		if (key == NO)
			data->path_no = str_extract(data->line, key);
		else if (key == SO)
			data->path_so = str_extract(data->line, key);
		else if (key == WE)
			data->path_we = str_extract(data->line, key);
		else if (key == EA)
			data->path_ea = str_extract(data->line, key);
		else if (key == C)
			data->c_color = ft_split(data->line, " \t");
		else if (key == F)
			data->f_color = ft_split(data->line, " \t");
		else if (key == ERROR)
			return (free(data->line), false);
		if (key != END)
			free(data->line);
		data->line = get_next_line(data->fd);
	}
	return (true);
}