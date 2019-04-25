#include "rsa.h"
#include "command.h"

void checkRsagen(t_sslarg *arg, struct s_command *command)
{
	t_rsagen *cmd;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_rsagen));
	ft_bzero(cmd, sizeof(t_rsagen));
	allowOptions(arg, (char*[]){"o", "rand", NULL});
	cmd->output = getContent(arg, "o");
	if (cmd->output)
		fdWriteAccess(cmd->output);
	cmd->random = getContent(arg, "rand");
	if (cmd->random)
		randomRead(NULL, 0, cmd->random);
	command->param = cmd;
}

void freeRsagen(t_rsagen *cmd)
{
	ft_memdel((void**)&cmd);
}

void executeRsagen(struct s_command *command)
{
	t_rsagen *cmd;

	cmd = command->param;
	t_rsakey *key = createRsaKey(ft_ssl_is_primary, 0.9999999);
	writeKey(key, 0, NULL);
	freeRsagen(cmd);
}
