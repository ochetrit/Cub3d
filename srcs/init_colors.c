/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:20 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/25 13:56:20 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	**build_color(char *line)
{
	int	**color;
	int	i;

	color = ft_calloc(sizeof(int *), 3);
	if (!color)
		return (ft_putstr_fd(ERR_MALLOC, STDERR), NULL);
	i = -1;
	while (++i < 3)
	{
		color[i] = ft_calloc(sizeof(int), 3);
		if (!color[i])
			return (ft_putstr_fd(ERR_MALLOC, STDERR), free_tab(color), NULL);
	}
}
