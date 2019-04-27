/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:25:22 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 20:32:39 by mdugot           ###   ########.fr       */
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
	check_command(arg);
	execute_command(arg);
	ft_lstdel(&arg->options, delete_pair);
	ft_memdel((void**)&arg);
	free_cmdlist();
	return (0);
}
