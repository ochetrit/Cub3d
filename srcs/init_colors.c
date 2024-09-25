/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:20 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/25 18:35:38 by ochetrit         ###   ########.fr       */
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
		while (line[i] < "255"[i])
			i++;
		if (i < 3)
			return (false);
	}
	return (true);
}

int	check_color(char *line)
{
	int	len;
	int	nb_pxl;

	while (*line != 'C' || *line != 'F')
		line++;
	line++;
	nb_pxl = 0;
	while (*line != '\n' || *line != '\0')
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (!ft_isdigit(*line))
			return (false);
		line++;
		len = 0;
		while (ft_isdigit(line[len]))
			len++;
		if (!check_is_char(line, len))
			return (false);
		line += len;
		nb_pxl++;
	}
	if (nb_pxl != 3)
		return (false);
	return (true);
}

int	check_comas(char *line, int comas[2])
{

	while (*line != 'C' || *line != 'F')
		line++;
	line++;
	if (*line != ' ' || *line != '\t')
		return (false);
	while (*line == ' ' || *line == '\t')
			line++;
	while (*line != '\n' || *line != '\0')
	{
		while (ft_isdigit(*line))
			line++;
		comas[1]++;
		while (*line == ' ' || *line == '\t' || *line == ',')
		{
			comas[0] = 0;
			if (*line == ',')
				comas[0]++;
			line++;
		}
		if ((comas[0] != 1 && comas[1] < 3) || (comas[0] != 0 && comas[1] == 3))
			return (false);
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
	fprintf(stderr, "TEST1\n");
	if (!check_color(line) || !check_comas(line, comas))
		return (NULL);
	printf("TEST2\n");
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
	}
	return (color);
}