/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:25:00 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/27 20:56:33 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*ft_maplast(t_map *lst)
{
	t_map	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_mapadd_back(t_map **head, t_map *new)
{
	t_map	*last;

	if (head)
	{
		if (*head)
		{
			last = ft_maplast(*head);
			last->next = new;
		}
		else
			*head = new;
	}
}

t_map	*ft_mapnew(char *line, int height)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
	{
		ft_putstr_fd(ERR_MALLOC, STDERR);
		return (NULL);
	}
	new->y_current = height;
	new->map = line;
	new->x_start = 0;
	while (line[new->x_start] && line[new->x_start] == ' ')
		new->x_start++;
	if (!line[new->x_start])
		return (free(line), new->map = NULL, new);
	new->next = NULL;
	return (new);
}