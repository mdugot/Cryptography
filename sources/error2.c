/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:39:31 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 11:10:06 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void		wrong_arg(t_sslarg *arg, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: [%s] %s\n", arg->command, message);
	exit(1);
}

void		basic_error(char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s\n", message);
	exit(1);
}

void		wrong_file(char *filename, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s: %s\n", filename, message);
	exit(1);
}

void		rsa_error(char *message)
{
	static int error = 0;

	if (message == NULL && error)
		exit(1);
	if (message)
	{
		ft_printf_fd(2, "RSA key error: %s\n", message);
		error = 1;
	}
}
