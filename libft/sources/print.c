/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 16:51:11 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:36:44 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prefix(char *str, char *prefix)
{
	char *result;

	result = ft_strnew(ft_strlen(str) + ft_strlen(prefix) + 1);
	ft_strcpy(result, prefix);
	ft_strcat(result, str);
	ft_strdel(&str);
	return (result);
}

char	*precise(char *str, t_value *v)
{
	int i;

	if (ACT_P == 0 || SPEC == '%')
		return (str);
	i = 0;
	if (SPEC == 's')
		while (str[i])
		{
			if (i == v->precision)
				str[i] = '\0';
			i++;
		}
	else if (!ft_strchr("cfF", SPEC))
		while (ft_strlen(str) - (*str == '-' ? 1 : 0) < (size_t)v->precision)
		{
			if (*str == '-')
			{
				*str = '0';
				str = prefix(str, "-");
			}
			else
				str = prefix(str, "0");
		}
	return (str);
}

char	*print_prefix(char *str, char c, t_printer *p, t_value *v)
{
	if (c != '0')
		return (str);
	if (ft_strchr("+- ", *str) && ft_strchr("idD?", SPEC))
	{
		printf_putchar(*str, p->fd, &p->result);
		str = &str[1];
	}
	else if (*str == '0' && str[1] && ft_strchr("xXbB", str[1]) && SPEC != 's')
	{
		printf_putchar(*str, p->fd, &p->result);
		printf_putchar(str[1], p->fd, &p->result);
		str = &str[2];
	}
	return (str);
}

void	print_with_width(char *str, t_value *v, t_printer *p)
{
	int		marge;
	char	c;
	int		len;

	len = SPEC == 'c' ? 1 : ft_strlen(str);
	marge = 0;
	while (marge + len < v->width)
		marge++;
	p->lenght += marge + len;
	c = ZERO ? '0' : ' ';
	if (RIGHT)
		print_str(str, v, p->fd);
	str = print_prefix(str, c, p, v);
	marge++;
	while (--marge)
		printf_putchar(c, p->fd, &p->result);
	if (!RIGHT)
		print_str(str, v, p->fd);
}

void	print_value(t_printer *p, t_value *v, char *str)
{
	int not_zero;

	not_zero = (*str == '0' ? 0 : 1);
	if (SPEC == 'c' && *str == 0)
		v->char_null = 1;
	if (!ft_strchr("sc", SPEC) && *str == '0' && v->precision == 0 && ACT_P)
		*str = 0;
	else
		str = precise(str, v);
	if ((SPEC == 'p') || (SPEC == 'x' && PREFIX && not_zero && *str != 0))
		str = prefix(str, "0x");
	if (SPEC == 'b' && PREFIX && *str != 0 && not_zero)
		str = prefix(str, "0b");
	if (SPEC == 'B' && PREFIX && *str != 0 && not_zero)
		str = prefix(str, "0B");
	if (SPEC == 'X' && PREFIX && *str != 0 && not_zero)
		str = prefix(str, "0X");
	if ((SPEC == 'o' || SPEC == 'O') && PREFIX && *str != 0 && *str != '0')
		str = prefix(str, "0");
	if (SIGNED && ft_strchr("dDifF", SPEC) && *str != '-')
		str = prefix(str, "+");
	if (BSIGNED && ft_strchr("dDifF", SPEC) && *str != '-')
		str = prefix(str, " ");
	print_with_width(str, v, p);
	ft_strdel(&str);
}
