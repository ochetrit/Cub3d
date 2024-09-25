/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:12 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/25 09:28:26 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		return (ft_putstr_fd(ERR_MALLOC, STDERR), NULL);
	key = -1;
	while (line[++key] && line[key] != ' ' && line[key] != '\t')
		str[key] = line[key];
	str[key] = '\0';
	while (line[key] && (line[key] == ' ' || line[key] == '\t'))
		key++;
	if (line[key] != '\n' || *str == '\0')
		return (free(str), NULL);
	return (str);
}

int	check_data_content(t_data *data)
{
	if (data->c_color)
		return (false);
	else if (data->f_color)
		return (false);
	else if (data->path_no)
		return (false);
	else if (data->path_so)
		return (false);
	else if (data->path_we)
		return (false);
	else if (data->path_ea)
		return (false);
	return (true);
}

int	find_path_and_color(t_data *data)
{
	int	key;

	data->line = get_next_line(data->fd);
	while (data->line && check_data_content(data))
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
			data->c_color = build_color(data->line);
		else if (key == F)
			data->f_color = build_color(data->line);
		else if (key == ERROR)
			return (free(data->line), false);
		if (key != END)
			free(data->line);
		data->line = get_next_line(data->fd);
	}
	return (true);
}
