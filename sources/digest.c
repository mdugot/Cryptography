/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:08:01 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 14:16:19 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "digest.h"
#include "command.h"

void			execute_digest_str(struct s_command *command, \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), \
		void (*print_result)(unsigned int *, char*, char*, t_digest *))
{
	t_digest		*cmd;
	int				i;
	unsigned int	*state;

	cmd = command->param;
	if (cmd->string)
	{
		i = 0;
		while (cmd->string[i])
		{
			arg_read_access(cmd->string[i]);
			state = hash(read_from_arg, digest, init_state, 0);
			print_result(state, cmd->string[i], NULL, cmd);
			ft_memdel((void**)&state);
			i++;
		}
	}
}

void			execute_digest(struct s_command *command, \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), \
		void (*print_result)(unsigned int *, char*, char*, t_digest *))
{
	t_digest		*cmd;
	int				i;
	unsigned int	*state;

	cmd = command->param;
	if ((!cmd->string && cmd->nfiles <= 0) || cmd->print_stdin)
	{
		state = hash(read_from_fd, digest, init_state, cmd->print_stdin);
		print_result(state, NULL, NULL, cmd);
		ft_memdel((void**)&state);
	}
	execute_digest_str(command, digest, init_state, print_result);
	i = 0;
	while (i < cmd->nfiles)
	{
		fd_read_access(cmd->files[i]);
		state = hash(read_from_fd, digest, init_state, 0);
		print_result(state, NULL, cmd->files[i], cmd);
		ft_memdel((void**)&state);
		i++;
	}
	free_digest(cmd);
}
