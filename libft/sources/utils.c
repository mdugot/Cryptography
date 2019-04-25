/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 18:13:23 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:30:43 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		read_joker(t_printer *p, char *flag)
{
	int r;

	r = va_arg(*(p->ap), int);
	p->format += 1;
	if (flag)
		*flag = 1;
	return (r);
}

void	print_color(char c, int fd, t_printer *p)
{
	if (c == 'R' || c == 'r')
		printf_putstr(C_RED, fd, &p->result);
	else if (c == 'G' || c == 'g')
		printf_putstr(C_GREEN, fd, &p->result);
	else if (c == 'Y' || c == 'y')
		printf_putstr(C_YELLOW, fd, &p->result);
	else if (c == 'B' || c == 'b')
		printf_putstr(C_BLUE, fd, &p->result);
	else if (c == 'M' || c == 'm')
		printf_putstr(C_MAGENTA, fd, &p->result);
	else if (c == 'C' || c == 'c')
		printf_putstr(C_CYAN, fd, &p->result);
	else if (c == 'W' || c == 'w')
		printf_putstr(C_WHITE, fd, &p->result);
	else if (c == 'N' || c == 'n')
		printf_putstr(C_NORMAL, fd, &p->result);
	else
		printf_putstr(RESET, fd, &p->result);
}

void	read_color(t_printer *p)
{
	print_color(p->format[0], p->fd, p);
	if (p->format[0])
		p->format += 1;
}

char	*one_char_str(char c)
{
	char *str;

	str = ft_strnew(2);
	str[0] = c;
	return (str);
}
