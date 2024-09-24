/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:29:01 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:11 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_malloc(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0 || ft_strlen(s) < start)
		return (0);
	while (s[start + i] != '\0' && i < len)
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (0);
	if (get_malloc(s, start, len))
	{
		res = malloc(sizeof(char) * (get_malloc(s, start, len) + 1));
		if (!res)
			return (NULL);
		i = 0;
		while (s[start] != '\0' && i < len)
		{
			res[i] = s[start];
			i++;
			start++;
		}
		res[i] = '\0';
		return (res);
	}
	res = (char *)malloc(sizeof(char));
	if (!res)
		return (NULL);
	*res = 0;
	return (res);
}

/* #include <stdio.h>


int	main(void)
{
	printf("%s\n",ft_substr("tripouille", 100, 1));
} */
