/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 12:28:43 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:22:45 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_between(t_printer *p, char *end)
{
	while (p->format < end)
	{
		printf_putchar(*(p->format), p->fd, &p->result);
		p->format += 1;
		p->lenght += 1;
	}
}

t_printer	initialize_printer(int fd, char *format, va_list *ap)
{
	t_printer p;

	if (fd > -1)
		p.result = NULL;
	else
		p.result = ft_strdup("");
	p.fd = fd;
	p.ap = ap;
	p.lenght = 0;
	p.format = format;
	return (p);
}

int			do_printf_fd(int fd, char *format, va_list *ap)
{
	char		*special;
	t_printer	p;

	p = initialize_printer(fd, format, ap);
	while (*(p.format))
	{
		special = find_next_special(p.format);
		print_between(&p, special);
		if (is_special(*(p.format)))
			read_special(&p);
	}
	va_end(*ap);
	return (p.lenght);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list	ap;

	va_start(ap, format);
	return (do_printf_fd(1, (char *)format, &ap));
}

int			ft_printf_fd(int fd, const char *restrict format, ...)
{
	va_list	ap;

	va_start(ap, format);
	return (do_printf_fd(fd, (char *)format, &ap));
}
