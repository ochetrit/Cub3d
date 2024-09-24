/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:37 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/22 18:00:39 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

void	write_word(char *dest, char const *from, char c)
{
	int	i;

	i = 0;
	while (from[i] != c && from[i])
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split(char **tab, char const *str, char c)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j])
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			write_word(tab[word], str + i, c);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		words;

	if (!str)
	{
		res = malloc(sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	words = count_words(str, c);
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		return (0);
	res[words] = NULL;
	write_split(res, str, c);
	return (res);
}

/* #include <stdio.h>

int	main(void)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split("chinimala", ' ');
	while(tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
 */