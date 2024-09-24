/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:29:27 by ochetrit          #+#    #+#             */
/*   Updated: 2024/03/11 03:50:48 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr2(const char *str, int character)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != (unsigned char)character)
		i++;
	if (str[i] == (unsigned char)character)
		return (i);
	return (-1);
}

char	*ft_strdup2(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	if (n == -1)
		return (NULL);
	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*free_temp(char *temp)
{
	free(temp);
	return (NULL);
}
