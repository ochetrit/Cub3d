/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:53 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/15 17:27:54 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_malloc(int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		return (1);
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	getnbr(int nbr, char *nb, int *i)
{
	if (nbr < 0)
	{
		nb[*i] = '-';
		*i = *i + 1;
		nbr = -nbr;
	}
	if (nbr >= 10)
		getnbr(nbr / 10, nb, &(*i));
	nb[*i] = "0123456789"[(nbr % 10)];
	*i = *i + 1;
}

char	*ft_itoa(int nbr)
{
	char	*nb;
	int		i;

	i = 0;
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	nb = malloc(sizeof(char) * (get_malloc(nbr) + 1));
	if (!nb)
		return (0);
	getnbr(nbr, nb, &i);
	nb[i] = '\0';
	return (nb);
}

/* #include <stdio.h>
#include <limits.h>

int	main(void)
{
	printf("%s\n", ft_itoa(INT_MIN));
} */