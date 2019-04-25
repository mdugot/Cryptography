/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 13:51:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:44:03 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_putchar(char c, int fd, char **to_join)
{
	char *tmp;

	if (*to_join == NULL)
		ft_putchar_fd(c, fd);
	else
	{
		tmp = ft_strnew(ft_strlen(*to_join) + 2);
		ft_strcpy(tmp, *to_join);
		tmp[ft_strlen(*to_join)] = c;
		ft_strdel(to_join);
		*to_join = tmp;
	}
}

void	printf_putstr(char *str, int fd, char **to_join)
{
	char *tmp;

	if (*to_join == NULL)
		ft_putstr_fd(str, fd);
	else
	{
		tmp = ft_strjoin(*to_join, str);
		ft_strdel(to_join);
		*to_join = tmp;
	}
}
