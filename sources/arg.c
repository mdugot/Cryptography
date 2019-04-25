/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:02:14 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 16:03:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

t_sslarg	*new_arg(int argc, char *argv[], t_list *o, char *c)
{
	t_sslarg *arg;

	arg = ft_memalloc(sizeof(t_sslarg));
	arg->argc = argc;
	arg->argv = argv;
	arg->options = o;
	arg->command = c;
	return (arg);
}

void		print_arg(t_sslarg *arg)
{
	int i;

	ft_printf_fd(2, "#RCOMMAND = %s#W\n", arg->command);
	ft_printf_fd(2, "#C");
	ft_lstiter(arg->options, print_option);
	ft_printf_fd(2, "#W");
	i = 0;
	while (i < arg->argc)
	{
		ft_printf_fd(2, "#M%s#W\n", arg->argv[i]);
		i++;
	}
}
