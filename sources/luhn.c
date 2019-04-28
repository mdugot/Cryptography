/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luhn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 10:57:14 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 13:39:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "luhn.h"
#include "command.h"

void		check_luhn(t_sslarg *arg, struct s_command *command)
{
	t_luhn				*cmd;
	char				*tmp;
	long long int		n;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_luhn));
	ft_bzero(cmd, sizeof(t_luhn));
	allow_options(arg, (char*[]){"m", NULL});
	tmp = get_content(arg, "m");
	if (!tmp)
		n = 10;
	else
		n = ft_atoi(tmp);
	cmd->modulus = n;
	if (n <= 1)
		wrong_arg(arg, "modulus must be greater than 2");
	if (arg->argc < 1)
		wrong_arg(arg, "expect one argument : card number");
	if (arg->argc > 1)
		wrong_arg(arg, ft_strf("unknown option '%s'", arg->argv[1]));
	n = ft_atol(arg->argv[0]);
	if (n < 0)
		wrong_arg(arg, "card number must be positive");
	cmd->number = n;
	command->param = cmd;
}

__uint64_t	luhn(__uint64_t number, __uint64_t mod)
{
	__uint64_t	result;
	__uint64_t	tmp;
	int			one_of_two;

	one_of_two = 0;
	result = 0;
	while (number)
	{
		tmp = number % mod;
		number /= mod;
		if (one_of_two)
		{
			tmp *= 2;
			if (tmp >= mod)
				tmp -= (mod - 1);
			one_of_two = 0;
		}
		else
			one_of_two = 1;
		result += tmp;
	}
	return (result % mod);
}

void		free_luhn(t_luhn *cmd)
{
	ft_memdel((void**)&cmd);
}

void		execute_luhn(struct s_command *command)
{
	t_luhn		*cmd;
	__uint64_t	result;

	cmd = command->param;
	result = luhn(cmd->number, cmd->modulus);
	ft_printf("luhn of %llu (mod %llu) is %llu\n", \
			cmd->number, cmd->modulus, result);
	if (result == 0)
		ft_printf("the number is valid.\n");
	else
		ft_printf("the number is invalid.\n");
	free_luhn(cmd);
}
