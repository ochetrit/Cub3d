/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:12 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/27 17:48:15 by ochetrit         ###   ########.fr       */
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
		return (ERROR);
}

int		len_path(char *line)
{
	int		len;

	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '\t' && line[len] != '\n')
		len++;
	return (len);
}

char	*str_extract(char *line, int *k)
{
	char	*str;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	line++;
	if (*k < C)
		line++;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*k = len_path(line);
	str = malloc(sizeof(char) * (*k + 1));
	if (!str)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), *k = ERROR, NULL);
	*k = -1;
	while (line[++*k] && line[*k] != ' ' && line[*k] != '\t' && line[*k] != '\n')
		str[*k] = line[*k];
	str[*k] = '\0';
	while (line[*k] && (line[*k] == ' ' || line[*k] == '\t'))
		*k += 1;
	if (line[*k] != '\n' || *str == '\0')
		return (free(str), *k = ERROR,  NULL);
	return (str);
}

int	check_data_content(t_data *data)
{
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
		if (key == NO)
			data->path_no = str_extract(data->line, &key);
		else if (key == SO)
			data->path_so = str_extract(data->line, &key);
		else if (key == WE)
			data->path_we = str_extract(data->line, &key);
		else if (key == EA)
			data->path_ea = str_extract(data->line, &key);
		else if (key == C)
			data->c_color = build_color(data->line, &key);
		else if (key == F)
			data->f_color = build_color(data->line, &key);
		if (key == ERROR)
			return (free(data->line), get_next_line(data->fd, true), false);
		free(data->line);
		if (!check_data_content(data))
			return (true);
		data->line = get_next_line(data->fd, false);
	}
	return (false);
	}
