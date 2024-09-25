/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:20 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/25 19:46:34 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_is_char(char *line, int len)
{
	int	i;

	i = 0;
	if (len > 3 || len == 0)
		return (false);
	if (len == 3)
	{
		while (line[i] - "255"[i] <= 0 && "255"[i])
			i++;
		if (i != 3)
			return (ft_putstr_fd(ERR_CHAR, STDERR), false);
	}
	return (true);
}

int	check_color(char *line)
{
	int	len;
	int	nb_pxl;

	while (*line != 'C' && *line != 'F' && *line)
		line++;
	line++;
	nb_pxl = 0;
	while (*line != '\n' && *line != '\0')
	{
		while ((*line == ' ' || *line == '\t' || *line == ',') && *line)
			line++;
		if (!ft_isdigit(*line))
			return (ft_putstr_fd(ERR_COLOR, STDERR), false);
		len = 0;
		while (ft_isdigit(line[len]))
			len++;
		if (!check_is_char(line, len))
			return (ft_putstr_fd(ERR_CHAR, STDERR), false);
		line += len;
		while ((*line == ' ' || *line == '\t' || *line == ',') && *line)
			line++;
		nb_pxl++;
	}
	if (nb_pxl != 3)
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
			return (printf("TEST\n"), false);
	}
	return (true);
}

char	**build_color(char *line)
{
	char	**color;
	int		comas[2];
	int	i;

	comas[0] = 0;
	comas[1] = 0;
	if (!check_color(line))
		return (NULL);
	if (!check_comas(line, comas))
		return (printf("oeoeoeoe\n"), NULL);
	color = ft_calloc(sizeof(char *), 3);
	if (!color)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), NULL);
	i = 0;
	while (*line && i < 3)
	{
		while (!ft_isdigit(*line))
			line++;
		color[i] = ft_itoa(ft_atoi(line));
		while (ft_isdigit(*line))
			line++;
		i++;
	}
	return (color);
}
