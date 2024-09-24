/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:35 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 18:31:13 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (s[i] && f)
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/*
void	test(unsigned int i , char* s)
{
	*s = '!';
}

#include <stdio.h>

int	main(int argc, char** argv)
{
	argc++;
	printf("%s\n", argv[1]);
	ft_striteri(argv[1], test);
	printf("%s\n", argv[1]);
} */