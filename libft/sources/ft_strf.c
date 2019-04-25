/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:43:56 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:47:22 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

char	*ft_strf(const char *restrict format, ...)
{
	char		*special;
	va_list		ap;
	t_printer	p;

	va_start(ap, format);
	p = initialize_printer(-1, (char *)format, &ap);
	while (*(p.format))
	{
		special = find_next_special(p.format);
		print_between(&p, special);
		if (is_special(*(p.format)))
			read_special(&p);
	}
	va_end(ap);
	return (p.result);
}
