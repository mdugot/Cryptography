/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:08:01 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:33:04 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "digest.h"
#include "command.h"

void			execute_digest_str(struct s_command *command, \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), \
		void (*print_result)(unsigned int *, char*, char*, t_digest *))
{
	t_digest	*cmd;
	int			i;

	cmd = command->param;
	if (cmd->string)
	{
		i = 0;
		while (cmd->string[i])
		{
			arg_read_access(cmd->string[i]);
			print_result(
				hash(read_from_arg, digest, init_state, 0),
				cmd->string[i], NULL, cmd);
			i++;
		}
	}
}

void			execute_digest(struct s_command *command, \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), \
		void (*print_result)(unsigned int *, char*, char*, t_digest *))
{
	t_digest	*cmd;
	int			i;

	cmd = command->param;
	if ((!cmd->string && cmd->nfiles <= 0) || cmd->print_stdin)
	{
		print_result(
			hash(read_from_fd, digest, init_state, cmd->print_stdin),
			NULL, NULL, cmd);
	}
	execute_digest_str(command, digest, init_state, print_result);
	i = 0;
	while (i < cmd->nfiles)
	{
		ft_printf("file : %s\n", cmd->files[i]);
		fd_read_access(cmd->files[i]);
		print_result(
			hash(read_from_fd, digest, init_state, 0),
			NULL, cmd->files[i], cmd);
		i++;
	}
	free_digest(cmd);
}
