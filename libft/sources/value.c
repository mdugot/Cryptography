/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:37:53 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/21 13:58:54 by tomo-chan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*vtoa_special(t_value *v, t_printer *p, t_arg arg)
{
	int base;

	if (SPEC == 'b' || SPEC == 'B')
		return (ft_uitoa_base(arg.a_uint, 2, 0));
	else
	{
		base = va_arg(*(p->ap), int);
		if (base < 2 || base > 36)
			base = 10;
		return (ft_itoa_base(arg.a_int, base));
	}
}

char	*vtoa(t_value *v, t_printer *p)
{
	t_arg arg;

	if (!is_specifier(SPEC))
		return (one_char_str(SPEC));
	arg = find_type(p->ap, v);
	if (SPEC == 's' && arg.a_str != NULL)
		return (ft_strdup(arg.a_str));
	else if (SPEC == 'c')
		return (one_char_str(arg.a_char));
	else if (SPEC == 'd' || SPEC == 'D' || SPEC == 'i')
		return (ft_itoa_base(arg.a_int, 10));
	else if (SPEC == 'f' || SPEC == 'F')
		return (ft_ftoa(arg.a_double, (ACT_P ? v->precision : 6)));
	else if (SPEC == 'u' || SPEC == 'U')
		return (ft_uitoa_base(arg.a_uint, 10, 1));
	else if (SPEC == 'x' || SPEC == 'X')
		return (ft_uitoa_base(arg.a_uint, 16, ft_isupper(SPEC)));
	else if (SPEC == 'o' || SPEC == 'O')
		return (ft_uitoa_base(arg.a_uint, 8, 0));
	else if (SPEC == 'p')
		return (ft_uitoa_base(arg.a_uint, 16, 0));
	else if (ft_strchr("bB?", SPEC))
		return (vtoa_special(v, p, arg));
	else
		return (ft_strdup("(null)"));
}

void	fill_null(US null[7])
{
	null[0] = '(';
	null[1] = 'n';
	null[2] = 'u';
	null[3] = 'l';
	null[4] = 'l';
	null[5] = ')';
	null[6] = 0;
}

void	unicode_value(t_value *v, t_printer *p)
{
	t_arg	arg;
	US		null[7];

	fill_null(null);
	arg = find_type(p->ap, v);
	if (SPEC == 'S' || SPEC == 's')
	{
		if (arg.a_wstr == NULL)
			wprint_value(p, v, null);
		else
			wprint_value(p, v, arg.a_wstr);
	}
	else
		wprint_value(p, v, &(arg.a_wchar));
}

void	write_value(t_value *v, t_printer *p)
{
	char	*str;

	if (SPEC == 0)
		return ;
	else if (SPEC == 'C' || (SPEC == 'c' && v->ss == L))
		unicode_value(v, p);
	else if (SPEC == 'S' || (SPEC == 's' && v->ss == L))
		unicode_value(v, p);
	else
	{
		str = vtoa(v, p);
		print_value(p, v, str);
	}
}
