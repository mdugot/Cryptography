/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:46:01 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:44:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

unsigned int	do_mask(US c, US mask, US apply_mask)
{
	unsigned int	result;
	unsigned int	cursor_mask;
	unsigned int	cursor_c;

	cursor_mask = 1;
	cursor_c = 1;
	result = 0;
	while (cursor_mask != 0x80000000)
	{
		if (cursor_mask & apply_mask)
			result = result | (cursor_mask & mask);
		else
		{
			if (cursor_c & c)
				result = result | cursor_mask;
			cursor_c = cursor_c << 1;
		}
		cursor_mask = cursor_mask << 1;
	}
	return (result);
}

void			write_char(unsigned char c, int fd, char **result)
{
	char *tmp;

	if (*result == NULL)
	{
		write(1, &c, fd);
	}
	else
	{
		tmp = ft_strnew(ft_strlen(*result) + 2);
		ft_strcpy(tmp, *result);
		tmp[ft_strlen(*result)] = c;
		ft_strdel(result);
		*result = tmp;
	}
}

void			ft_putoctet_fd(unsigned char *c, int n, int fd, char **result)
{
	if (n == 1)
		write_char(c[0], fd, result);
	else if (n == 2)
	{
		write_char(c[1], fd, result);
		write_char(c[0], fd, result);
	}
	else if (n == 3)
	{
		write_char(c[2], fd, result);
		write_char(c[1], fd, result);
		write_char(c[0], fd, result);
	}
	else
	{
		write_char(c[3], fd, result);
		write_char(c[2], fd, result);
		write_char(c[1], fd, result);
		write_char(c[0], fd, result);
	}
}

void			ft_putwchar_fd(unsigned int c, int fd, char **result)
{
	int				sb;

	sb = significant_bit(&c, 4);
	if (sb <= 7)
		ft_putchar_fd(c, fd);
	else if (sb <= 11)
	{
		c = do_mask(c, 0xC080, 0xE0C0);
		ft_putoctet_fd((unsigned char*)&c, 2, fd, result);
	}
	else if (sb <= 16)
	{
		c = do_mask(c, 0xE08080, 0xF0C0C0);
		ft_putoctet_fd((unsigned char*)&c, 3, fd, result);
	}
	else
	{
		c = do_mask(c, 0xF0808080, 0xF8C0C0C0);
		ft_putoctet_fd((unsigned char*)&c, 4, fd, result);
	}
}
