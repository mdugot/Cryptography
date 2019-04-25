/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:25:22 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 17:26:34 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "des.h"
#include "base64.h"
#include "miller_rabin.h"
#include "rsa.h"

int		main(int argc, char *argv[])
{
	t_sslarg	*arg;

	init_all_commands();
	arg = parse_options(argc, argv);
	print_arg(arg);
	check_command(arg);
	execute_command(arg);
	ft_putendl("");
	return (0);
}
