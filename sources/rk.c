/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rk.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:03:07 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 16:53:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rk.h"
#include "command.h"

void		check_rk(t_sslarg *arg, struct s_command *command)
{
	t_rk	*cmd;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_rk));
	ft_bzero(cmd, sizeof(t_rk));
	allow_options(arg, (char*[]){"file", "string", "search", NULL});
	cmd->ftext = get_content(arg, "file");
	cmd->stext = get_content(arg, "string");
	cmd->search = get_content(arg, "search");
	if ((cmd->ftext && cmd->stext) || (!cmd->ftext && !cmd->stext))
		wrong_arg(arg, "expect only one of '-file' and '-string'");
	if (!cmd->search)
		wrong_arg(arg, "option '-search' mandatory");
	if (cmd->ftext)
	{
		fd_read_access(cmd->ftext);
		cmd->reader = read_from_fd;
	}
	else
	{
		arg_read_access(cmd->stext);
		cmd->reader = read_from_arg;
	}
	command->param = cmd;
}

void		free_rk(t_rk *cmd)
{
	ft_strdel(&cmd->window_buff);
	ft_memdel((void**)&cmd);
}

void		execute_rk(struct s_command *command)
{
	t_rk		*cmd;

	cmd = command->param;
	cmd->hash = 0;
	cmd->idx = 0;
	cmd->found = 0;
	cmd->len = ft_strlen(cmd->search);
	cmd->whash = rk_hash(cmd->search, cmd->len);
	cmd->window_buff = ft_strnew(cmd->len);
	if (cmd->len == 0)
		cmd->found = 1;
	else
		rabin_karp(cmd);
	if (cmd->found)
		ft_printf("'%s' found at index %zu\n", \
			cmd->search, cmd->idx + 1 - cmd->len);
	else
		ft_printf("'%s' not found\n", cmd->search);
	free_rk(cmd);
}
