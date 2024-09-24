/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:10:17 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:17:10 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list args, int std, const char *format)
{
	int	n_oct;

	if (*format == 'c')
		n_oct = ft_putchar(va_arg(args, int), std);
	else if (*format == 's')
		n_oct = ft_putstr(va_arg(args, char *), std);
	else if (ft_strchr3("di", *format))
		n_oct = ft_putnbr(va_arg(args, int), std);
	else if (*format == 'u')
		n_oct = ft_putnbr_unsigned(va_arg(args, unsigned int), std);
	else if (*format == 'p')
		n_oct = ft_puthex(va_arg(args, unsigned long), 'x', 'Y', std);
	else if (ft_strchr3("xX", *format))
		n_oct = ft_puthex(va_arg(args, unsigned int), *format, 'n', std);
	else
		n_oct = write(std, "%", 1);
	return (n_oct);
}

int	ft_printf(const char *format, int std, ...)
{
	int		n_oct;
	va_list	args;

	if (ft_check(format) == -1)
		return (-1);
	va_start(args, std);
	n_oct = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				n_oct += ft_format(args, std, format);
		}
		else
			n_oct += write(std, format, 1);
		format++;
	}
	va_end(args);
	return (n_oct);
}
