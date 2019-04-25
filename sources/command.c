#include "command.h"

t_list	*cmdlist = NULL;

void	initAllCommands()
{
	newCommand("md5", &cmdlist, checkDigest, executeMD5);
	newCommand("sha256", &cmdlist, checkDigest, executeSHA256);
	newCommand("base64", &cmdlist, check64, execute64);
	newCommand("des", &cmdlist, checkDES, executeDES);
	newCommand("des-ecb", &cmdlist, checkDES, executeDES);
	newCommand("des-cbc", &cmdlist, checkDES, executeDES);
	newCommand("genrsa", &cmdlist, checkRsagen, executeRsagen);
	newCommand("rsa", &cmdlist, checkRsacmd, executeRsacmd);
	newCommand("rsautl", &cmdlist, checkRsautl, executeRsautl);
}

void	executeCommand(t_sslarg *arg)
{
	t_command *command;

	command = findCommand(cmdlist, arg->command);
	if (command == NULL)
	{
		wrongCommand(ft_strf("unknown command : %s", arg->command));
	}
	command->checker(arg, command);
	command->executer(command);
}

t_command	*findCommand(t_list *tmp, char *name)
{
	t_command	*cmd;

	while (tmp)
	{
		cmd = (t_command*)tmp->content;
		if (ft_strcmp(cmd->name, name) == 0)
			return cmd;
		tmp = tmp->next;
	}
	return NULL;
}

t_command	*newCommand(char *name, t_list **cmdlist,\
			void (*checker)(t_sslarg* arg, struct s_command* command),\
			void (*executer)(struct s_command* command))
{
	t_command *cmd;

	cmd = ft_memalloc(sizeof(t_command));
	ft_bzero(cmd, sizeof(t_command));
	ft_strcpy(cmd->name, name);
	cmd->checker = checker;
	cmd->executer = executer;
	ft_lstadd_end(cmdlist, ft_lstnew_noalloc((void*)cmd, sizeof(t_command)));
	return cmd;
}
