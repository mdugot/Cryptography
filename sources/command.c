/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:22:16 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 17:41:19 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_list	*g_cmdlist = NULL;

void		init_all_commands(void)
{
	new_command("md5", &g_cmdlist, check_digest, execute_md5);
	new_command("sha256", &g_cmdlist, check_digest, execute_sha_256);
	new_command("base64", &g_cmdlist, check_64, execute_64);
	new_command("des", &g_cmdlist, check_des, execute_des);
	new_command("des-ecb", &g_cmdlist, check_des, execute_des);
	new_command("des-cbc", &g_cmdlist, check_des, execute_des);
	new_command("genrsa", &g_cmdlist, check_rsagen, execute_rsagen);
	new_command("rsa", &g_cmdlist, check_rsacmd, execute_rsacmd);
	new_command("rsautl", &g_cmdlist, check_rsautl, execute_rsautl);
}

void		free_cmdlist()
{
	ft_lstfree(&g_cmdlist);
}

void		execute_command(t_sslarg *arg)
{
	t_command *command;

	command = find_command(g_cmdlist, arg->command);
	if (command == NULL)
	{
		wrong_command(ft_strf("unknown command : %s", arg->command));
	}
	command->checker(arg, command);
	command->executer(command);
}

t_command	*find_command(t_list *tmp, char *name)
{
	t_command	*cmd;

	while (tmp)
	{
		cmd = (t_command*)tmp->content;
		if (ft_strcmp(cmd->name, name) == 0)
			return (cmd);
		tmp = tmp->next;
	}
	return (NULL);
}

t_command	*new_command(char *name, t_list **cmdlist,\
			void (*checker)(t_sslarg *arg, struct s_command *command),\
			void (*executer)(struct s_command *command))
{
	t_command *cmd;

	cmd = ft_memalloc(sizeof(t_command));
	ft_bzero(cmd, sizeof(t_command));
	ft_strcpy(cmd->name, name);
	cmd->checker = checker;
	cmd->executer = executer;
	ft_lstadd_end(cmdlist, ft_lstnew_noalloc((void*)cmd, sizeof(t_command)));
	return (cmd);
}
