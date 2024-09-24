/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:57 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/08 12:01:18 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	if (!s)
		return (0);
	res = ft_strdup(s);
	if (!res)
		return (0);
	i = 0;
	while (res[i] && f)
	{
		res[i] = f(i, res[i]);
		i++;
	}
	return (res);
}

/* 
char	test(unsigned int i , char s)
{
	i++;
	s = '!';
	return(s);
}

#include <stdio.h>

int	main(int argc, char** argv)
{
	argc++;
	char *res;

	printf("%s\n", argv[1]);
	res = ft_strmapi(argv[1], test);
	printf("%s\n", res);
} */