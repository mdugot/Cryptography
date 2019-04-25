/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 16:28:22 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:25:53 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*update_flags(t_value *v, char *c)
{
	if (*c == '#')
		v->flags.prefix = 1;
	if (*c == '+')
		v->flags.forced_sign = 1;
	if (*c == '0')
		v->flags.zero_blank = 1;
	if (*c == '-')
		v->flags.right_blank = 1;
	if (*c == ' ')
		v->flags.blank_sign = 1;
	if (*c == 'h' && c[1] == 'h' && v->ss < HH)
		v->ss = HH;
	else if (*c == 'h' && v->ss < H)
		v->ss = H;
	else if (*c == 'l' && c[1] != 'l' && v->ss < L)
		v->ss = L;
	else if (*c == 'l' && c[1] == 'l' && v->ss < LL)
		v->ss = LL;
	else if (*c == 'j' && v->ss < J)
		v->ss = J;
	else if (*c == 'z' && v->ss < Z)
		v->ss = Z;
	if ((*c == 'h' || *c == 'l') && *c == c[1])
		c++;
	return (c);
}

void	read_width_precision(t_printer *p, t_value *v)
{
	if (ft_isdigit(*(p->format)))
	{
		v->active_width = 1;
		v->width = ft_atoi(p->format);
		while (ft_isdigit(*(p->format)))
			p->format += 1;
	}
	else if (p->format[0] == '*')
		v->width = read_joker(p, &(v->active_width));
	if (*(p->format) == '.')
	{
		p->format += 1;
		if (p->format[0] == '*')
			v->precision = read_joker(p, &(v->active_precision));
		else
		{
			v->active_precision = 1;
			v->precision = ft_atoi(p->format);
			while (ft_isdigit(*(p->format)))
				p->format += 1;
		}
	}
}

void	update_value(t_value *v, int end, t_printer *p)
{
	if (end == 0 && p->format[0])
	{
		v->specifier = *(p->format);
		p->format += 1;
	}
	if (v->precision < 0)
		ACT_P = 0;
	if ((ZERO && RIGHT) || (ACT_P && ft_strchr("diouixDOXbB?", SPEC)))
		ZERO = 0;
	if (PREFIX && ft_strchr("cdinpsCDSu?", SPEC))
		PREFIX = 0;
	if (PREFIX && ft_strchr("oO", SPEC) && v->precision < 1)
	{
		ACT_P = 1;
		v->precision = 1;
	}
	if (SIGNED && BSIGNED)
		BSIGNED = 0;
	if (v->width < 0)
	{
		v->width *= -1;
		RIGHT = RIGHT ? 0 : 1;
	}
}

t_value	read_value(t_printer *p)
{
	t_value	v;
	int		end;

	ft_bzero(&v, sizeof(v));
	v.printer = p;
	end = 0;
	while (!end && is_expr(*(p->format)))
	{
		while (is_flag(*(p->format)))
		{
			p->format = update_flags(&v, p->format);
			p->format += 1;
		}
		read_width_precision(p, &v);
		if (is_specifier(*(p->format)))
		{
			v.specifier = *(p->format);
			p->format += 1;
			end = 1;
		}
	}
	update_value(&v, end, p);
	return (v);
}

void	read_special(t_printer *p)
{
	char		*c;
	t_value		v;

	c = p->format;
	p->format += 1;
	if (*c == c[1])
	{
		p->lenght += 1;
		printf_putchar(*c, p->fd, &p->result);
		p->format += 1;
		return ;
	}
	if (*c == '#')
	{
		read_color(p);
		return ;
	}
	if (!is_expr(p->format[0]))
		return ;
	ft_bzero(&v, sizeof(t_value));
	if (*c == '%')
	{
		v = read_value(p);
		write_value(&v, p);
	}
}
