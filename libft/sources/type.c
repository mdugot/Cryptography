/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:06:06 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/18 14:31:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_type_str(t_arg *arg, va_list *ap, t_value *v)
{
	if (v->ss == L || SPEC == 'S')
		arg->a_wstr = (unsigned int*)va_arg(*ap, unsigned int*);
	else
		arg->a_str = (char*)va_arg(*ap, char*);
}

void	find_type_c(t_arg *arg, va_list *ap, t_value *v)
{
	if (v->ss == L || SPEC == 'C')
		arg->a_wchar = (unsigned int)va_arg(*ap, unsigned int);
	else
		arg->a_char = (char)va_arg(*ap, int);
}

void	find_type_int(t_arg *arg, va_list *ap, t_value *v)
{
	if (ft_isupper(SPEC))
		arg->a_int = (long int)va_arg(*ap, long int);
	else if (v->ss == HH)
		arg->a_int = (char)va_arg(*ap, int);
	else if (v->ss == H)
		arg->a_int = (short int)va_arg(*ap, int);
	else if (v->ss == L)
		arg->a_int = (long int)va_arg(*ap, long int);
	else if (v->ss == LL)
		arg->a_int = (long long int)va_arg(*ap, long long int);
	else if (v->ss == J)
		arg->a_int = (intmax_t)va_arg(*ap, intmax_t);
	else if (v->ss == Z)
		arg->a_int = (size_t)va_arg(*ap, size_t);
	else
		arg->a_int = va_arg(*ap, int);
}

void	find_type_unsign(t_arg *arg, va_list *ap, t_value *v)
{
	if (ft_isupper(SPEC) && SPEC != 'X' && SPEC != 'B')
		arg->a_uint = va_arg(*ap, unsigned long int);
	else if (v->ss == HH)
		arg->a_uint = (unsigned char)va_arg(*ap, int);
	else if (v->ss == H)
		arg->a_uint = (unsigned short int)va_arg(*ap, int);
	else if (v->ss == L)
		arg->a_uint = va_arg(*ap, unsigned long int);
	else if (v->ss == LL)
		arg->a_uint = va_arg(*ap, unsigned long long int);
	else if (v->ss == J)
		arg->a_uint = va_arg(*ap, uintmax_t);
	else if (v->ss == Z)
		arg->a_uint = va_arg(*ap, size_t);
	else
		arg->a_uint = va_arg(*ap, unsigned int);
}

t_arg	find_type(va_list *ap, t_value *v)
{
	t_arg result;

	ft_bzero(&result, sizeof(result));
	if (SPEC == 'd' || SPEC == 'D' || SPEC == 'i' || SPEC == '?')
		find_type_int(&result, ap, v);
	else if (ft_strchr("uUoOxXbB", SPEC))
		find_type_unsign(&result, ap, v);
	else if (SPEC == 'c' || SPEC == 'C')
		find_type_c(&result, ap, v);
	else if (SPEC == 's' || SPEC == 'S')
		find_type_str(&result, ap, v);
	else if (SPEC == 'f' || SPEC == 'F')
		result.a_double = va_arg(*ap, double);
	else
		result.a_ad = va_arg(*ap, void*);
	return (result);
}
