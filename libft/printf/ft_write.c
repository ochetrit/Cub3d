/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:41:05 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:17:18 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int std)
{
	char	d;

	d = (char)c;
	return (write(std, &d, 1));
}

int	ft_putstr(const char *format, int std)
{
	int	n_oct;

	n_oct = 0;
	if (!format)
		return (write(std, "(null)", 6));
	while (*format)
	{
		write(std, format, 1);
		format++;
		n_oct++;
	}
	return (n_oct);
}

int	ft_putnbr(int nb, int std)
{
	int				len;
	unsigned int	nbr;

	len = 0;
	nbr = nb;
	if (nb < 0)
	{
		write(std, "-", 1);
		nbr = -nb;
		len++;
	}
	if (nbr > 9)
		len += ft_putnbr(nbr / 10, std);
	return (len + write(std, &"0123456789"[nbr % 10], 1));
}

int	ft_putnbr_unsigned(unsigned int nb, int std)
{
	int	len;

	len = 0;
	if (nb > 9)
		len += ft_putnbr(nb / 10, std);
	len += write(std, &"0123456789"[nb % 10], 1);
	return (len);
}

int	ft_puthex(unsigned long nb, char key, char ptr, int std)
{
	int	len;

	len = 0;
	if (ptr == 'Y')
	{
		if (nb == 0)
			return (write(std, "(nil)", 5));
		len += write(std, "0x", 2);
	}
	if (nb > 15)
		len += ft_puthex(nb / 16, key, 'n', std);
	if (key == 'x')
		return (len + write(std, &"0123456789abcdef"[nb % 16], 1));
	return (len + write(std, &"0123456789ABCDEF"[nb % 16], 1));
}
