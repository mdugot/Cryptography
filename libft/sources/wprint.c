/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:39:42 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:32:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		size_wchar(US c)
{
	int	sb;

	sb = significant_bit(&c, 4);
	if (sb <= 7)
		return (1);
	else if (sb <= 11)
		return (2);
	else if (sb <= 16)
		return (3);
	else
		return (4);
}

int		wprecise(US *str, t_value *v)
{
	int		i;
	int		n;

	if (ACT_P == 0 || SPEC == 'c' || SPEC == 'C')
		return (-1);
	i = 0;
	n = 0;
	if (SPEC == 's' || SPEC == 'S')
		while (str[i])
		{
			n += size_wchar(str[i]);
			if (n > v->precision)
				return (i);
			i++;
		}
	return (i);
}

int		size_unicode(US *str, int size)
{
	int r;
	int i;

	r = 0;
	i = 0;
	while (str[i])
	{
		if (i >= size && size >= 0)
			return (r);
		r += size_wchar(str[i]);
		i++;
	}
	return (r);
}

void	wprint_with_width(US *str, t_value *v, t_printer *p, int size)
{
	int		marge;
	char	c;
	int		len;

	len = ft_strchr("Cc", SPEC) ? size_wchar(*str) : size_unicode(str, size);
	marge = 0;
	while (marge + len < v->width)
		marge++;
	p->lenght += marge + len;
	if (ZERO)
		c = '0';
	else
		c = ' ';
	if (RIGHT)
		wprint_str(str, v, p->fd, size);
	while (marge)
	{
		printf_putchar(c, p->fd, &p->result);
		marge--;
	}
	if (!RIGHT)
		wprint_str(str, v, p->fd, size);
}

void	wprint_value(t_printer *p, t_value *v, US *str)
{
	int size;

	if ((SPEC == 'c' || SPEC == 'C') && *str == 0)
		v->char_null = 1;
	size = wprecise(str, v);
	wprint_with_width(str, v, p, size);
}
