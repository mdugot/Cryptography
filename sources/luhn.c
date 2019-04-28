/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luhn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 10:57:14 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 11:10:03 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "luhn.h"

void	check_luhn(t_sslarg *arg, struct s_command *command)
{
	t_luhn	*cmd;
	char	*tmp;
	int		n;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_luhn));
	ft_bzero(cmd, sizeof(t_luhn));
	allow_options(arg, (char*[]){"m", NULL});
	tmp = get_content(arg, "m");
	if (!tmp)
		n = 10;
	else
		n = ft_atoi(tmp);
	if (n < 0)
		wrong_arg(arg, "modulus must be positive");
	if (arg->argc != 1)
		wrong_arg(arg, "expect one argument : card number");
	n = ft_atoi(arg->argv[0]);
	if (n < 0)
		wrong_arg(arg, "card number must be positive");
	cmd->number = n;
	command->param = cmd;
}

void	free_luhn(t_rsagen *cmd)
{
	ft_memdel((void**)&cmd);
}

void	execute_luhn(struct s_command *command)
{
	t_luhn *cmd;

	cmd = command->param;
	ft_printf("LUHN : %llu (mod %llu)\n", cmd->number, cmd->modulus
	free_lunh(cmd);
}
