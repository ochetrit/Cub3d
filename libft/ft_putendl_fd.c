/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:51 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/08 10:57:47 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	if (fd != -1 && str != NULL)
	{
		while (*str != '\0')
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
		ft_putchar_fd('\n', fd);
	}
}
