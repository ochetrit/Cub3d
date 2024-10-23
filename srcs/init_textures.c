/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:12 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/23 17:52:55 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	which_one(char *line)
{
	if (!line)
		return (END);
	else if (!*line)
		return (EMPTY);
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	if (!*line)
		return (EMPTY);
	else if (!ft_strncmp(line, "NO", 2))
		return (NO);
	else if (!ft_strncmp(line, "SO", 2))
		return (SO);
	else if (!ft_strncmp(line, "WE", 2))
		return (WE);
	else if (!ft_strncmp(line, "EA", 2))
		return (EA);
	else if (!ft_strncmp(line, "C", 1))
		return (C);
	else if (!ft_strncmp(line, "F", 1))
		return (F);
	else
		return (ft_putstr_fd(ERR_FORM, STDERR), ERROR);
}

char	*str_extract(char *line, int *k)
{
	char	*str;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*k = len_path(line);
	if (*k > 2)
		return (ft_putstr_fd(ERR_KEY, STDERR), *k = ERROR, NULL);
	line += *k;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*k = len_path(line);
	str = malloc(sizeof(char) * (*k + 1));
	if (!str)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), *k = ERROR, NULL);
	*k = -1;
	while (line[++*k] && line[*k] != ' '
		&& line[*k] != '\t' && line[*k] != '\n')
		str[*k] = line[*k];
	str[*k] = '\0';
	while (line[*k] && (line[*k] == ' ' || line[*k] == '\t'))
		*k += 1;
	if (line[*k] != '\n')
		return (free(str), ft_putstr_fd(ERR_FORM, STDERR), *k = ERROR, NULL);
	return (str);
}

int	check_data_content(t_data *data)
{
	free(data->line);
	if (!data->c_color)
		return (true);
	else if (!data->f_color)
		return (true);
	else if (!data->path_no)
		return (true);
	else if (!data->path_so)
		return (true);
	else if (!data->path_we)
		return (true);
	else if (!data->path_ea)
		return (true);
	return (false);
}

int	find_path_and_color(t_data *data)
{
	int	key;

	data->line = get_next_line(data->fd, false);
	while (data->line)
	{
		key = which_one(data->line);
		if (key == NO && check_if_exists(&key, data))
			data->path_no = str_extract(data->line, &key);
		else if (key == SO && check_if_exists(&key, data))
			data->path_so = str_extract(data->line, &key);
		else if (key == WE && check_if_exists(&key, data))
			data->path_we = str_extract(data->line, &key);
		else if (key == EA && check_if_exists(&key, data))
			data->path_ea = str_extract(data->line, &key);
		else if (key == C && check_if_exists(&key, data))
			data->c_color = build_color(data->line, &key);
		else if (key == F && check_if_exists(&key, data))
			data->f_color = build_color(data->line, &key);
		if (key == ERROR)
			return (free(data->line), get_next_line(data->fd, true), false);
		if (!check_data_content(data))
			return (true);
		data->line = get_next_line(data->fd, false);
	}
	return (false);
}
