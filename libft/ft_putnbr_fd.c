/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:43 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/09 16:52:13 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int		nbr;
	unsigned char	temp;

	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		write(fd, "-", 1);
	}
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	temp = '0' + (char)(nbr % 10);
	write(fd, &temp, 1);
}

/* #include<limits.h>

int	main(void)
{
	ft_putnbr_fd(INT_MIN,1);
} */