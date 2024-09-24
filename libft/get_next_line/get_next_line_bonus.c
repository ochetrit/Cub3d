/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:29:13 by ochetrit          #+#    #+#             */
/*   Updated: 2024/06/04 18:34:48 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*temp[FD_MAX];
	char		*str;
	int			size;
	int			i;

	if (ft_strchr2(temp[fd], '\n') == -1)
		temp[fd] = ft_initialise(temp[fd], fd);
	if (!temp[fd])
		return (free_temp(temp[fd]));
	size = ft_strchr2(temp[fd], '\n');
	if (size == -1)
	{
		str = ft_strdup2(temp[fd], ft_strlen2(temp[fd]));
		temp[fd] = free_temp(temp[fd]);
		return (str);
	}
	str = (char *)malloc((size + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i <= size)
		str[i] = temp[fd][i];
	str[i] = '\0';
	temp[fd] = ft_replace_temp(temp[fd], size);
	return (str);
}

char	*ft_initialise(char *temp, int fd)
{
	char	*stock;
	char	*new;
	int		n_oct;

	stock = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!stock)
		return (NULL);
	n_oct = read(fd, stock, BUFFER_SIZE);
	if (n_oct < 1)
		new = temp;
	else if (!temp)
		new = ft_strdup2(stock, n_oct);
	else
		new = ft_extend_temp(temp, stock, n_oct);
	free(stock);
	if (ft_strchr2(new, '\n') == -1 && n_oct >= 1)
		new = ft_initialise(new, fd);
	return (new);
}

char	*ft_extend_temp(char *temp, char stock[BUFFER_SIZE], int n_oct)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)malloc((ft_strlen2(temp) + n_oct + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		new[i] = temp[i];
		i++;
	}
	j = 0;
	while (j < n_oct)
	{
		new[i] = stock[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(temp);
	return (new);
}

char	*ft_replace_temp(char *temp, int i)
{
	char	*new;
	int		len;
	int		j;

	if (!temp[i + 1])
	{
		free(temp);
		return (NULL);
	}
	len = ft_strlen2(temp);
	new = (char *)malloc((len - i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	while (++i < len)
	{
		new[j] = temp[i];
		j++;
	}
	new[j] = '\0';
	free(temp);
	return (new);
}

/* int main(int ac, char **av)
{
	(void) av;
	(void) ac;
	char *str = "yo";
	int fd = open("florian.txt", O_RDONLY);
	while (str)
	{
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
} */