/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 15:46:50 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:38:36 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(char *str, t_value *v, int fd)
{
	printf_putstr(str, fd, &v->printer->result);
	if (v->char_null)
		printf_putchar(*str, fd, &v->printer->result);
}

void	wprint_str(US *str, t_value *v, int fd, int size)
{
	ft_putwstr_size_fd(str, fd, size, &v->printer->result);
	if (v->char_null)
		ft_putwchar_fd(*str, fd, &v->printer->result);
}
