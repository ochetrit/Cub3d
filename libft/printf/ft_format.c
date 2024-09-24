/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:05 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:17:05 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strchr3(const char *str, int character)
{
	while (*str && *str != (unsigned char)character)
		str++;
	if (*str == (unsigned char)character)
		return (1);
	return (0);
}

int	ft_check(const char *format)
{
	int			count;

	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_strchr3("cspdiuxX%", *format) && *format)
				count++;
			else
				return (-1);
		}
		format++;
	}
	return (count);
}
