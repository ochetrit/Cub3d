/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:20 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:17 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_is_char(char *line, int len)
{
	int	number;

	number = 0;
	if (len > 3 || len == 0)
		return (false);
	while (len > 0)
	{
		number += *line - '0';
		if (len > 1)
			number *= 10;
		line++;
		len--;
	}
	if (number < 0 || number > 255)
		return (false);
	return (true);
}

int	check_color(char *line)
{
	int	len[2];

	while (*line != 'C' && *line != 'F' && *line)
		line++;
	line++;
	len[0] = 0;
	while (*line != '\n' && *line != '\0')
	{
		while ((*line == ' ' || *line == '\t' || *line == ',') && *line)
			line++;
		if (!ft_isdigit(*line))
			return (ft_putstr_fd(ERR_COLOR, STDERR), false);
		len[1] = 0;
		while (ft_isdigit(line[len[1]]))
			len[1]++;
		if (!check_is_char(line, len[1]))
			return (ft_putstr_fd(ERR_CHAR, STDERR), false);
		line += len[1];
		while ((*line == ' ' || *line == '\t' || *line == ',') && *line)
			line++;
		len[0]++;
	}
	if (len[0] != 3)
		return (false);
	return (true);
}

int	check_comas(char *line, int comas[2])
{
	while (*line != 'C' && *line != 'F' && *line)
		line++;
	line++;
	if (*line != ' ' && *line != '\t')
		return (false);
	while (*line == ' ' || *line == '\t')
			line++;
	while (*line != '\n' && *line != '\0')
	{
		while (ft_isdigit(*line))
			line++;
		comas[1]++;
		comas[0] = 0;
		while (*line == ' ' || *line == '\t' || *line == ',')
		{
			if (*line == ',')
				comas[0]++;
			line++;
		}
		if ((comas[0] != 1 && comas[1] < 3) || (comas[0] != 0 && comas[1] == 3))
			return (false);
	}
	return (true);
}

unsigned char	*build_color(char *line, int *key)
{
	unsigned char	*color;
	int				comas[2];
	int				i;

	comas[0] = 0;
	comas[1] = 0;
	if (!check_color(line))
		return (*key = ERROR, NULL);
	if (!check_comas(line, comas))
		return (*key = ERROR, ft_putstr_fd(ERR_COLOR2, STDERR), NULL);
	color = ft_calloc(sizeof(char), 3);
	if (!color)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), *key = ERROR, NULL);
	i = 0;
	while (*line && i < 3)
	{
		while (!ft_isdigit(*line))
			line++;
		color[i] = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		i++;
	}
	return (color);
}

void	init_color_key(t_data *data)
{	
	data->c_color_key = data->c_color[0] << 16
		| data->c_color[1] << 8 | data->c_color[2];
	data->f_color_key = data->f_color[0] << 16
		| data->f_color[1] << 8 | data->f_color[2];
}
