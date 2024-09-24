/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:29:33 by ochetrit          #+#    #+#             */
/*   Updated: 2024/06/04 18:30:44 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*free_temp(char *temp);
char	*get_next_line(int fd);
char	*ft_initialise(char *temp, int fd);
char	*ft_replace_temp(char *temp, int i);
char	*ft_extend_temp(char *temp, char stock[BUFFER_SIZE], int n_oct);
char	*ft_strdup2(char *src, int n);
int		ft_strlen2(const char *str);
int		ft_strchr2(const char *str, int character);

#endif
