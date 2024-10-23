/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:52:10 by ochetrit          #+#    #+#             */
/*   Updated: 2024/10/23 17:56:04 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_if_exists(int *key, t_data *data)
{
	if (*key == NO && !data->path_no)
		return (true);
	else if (*key == SO && !data->path_so)
		return (true);
	else if (*key == WE && !data->path_we)
		return (true);
	else if (*key == EA && !data->path_ea)
		return (true);
	else if (*key == C && !data->c_color)
		return (true);
	else if (*key == F && !data->f_color)
		return (true);
	*key = ERROR;
	return (ft_putstr_fd(ERR_NB_KEY, STDERR), false);
}

int	len_path(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != ' '
		&& line[len] != '\t' && line[len] != '\n')
		len++;
	return (len);
}
