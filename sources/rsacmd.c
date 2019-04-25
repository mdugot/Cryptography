#include "rsa.h"
#include "command.h"

t_des *desForRsa(char *password, int decrypt)
{
	t_des *des;

	des = ft_memalloc(sizeof(t_des));
	ft_bzero(des, sizeof(t_des));
	des->rsa = 1;
	des->cbc = 1;
	des->password = password;
	des->decrypt = decrypt;
	des->base64 = 1;
	if (!decrypt)
	{
		des->writer = writeToFd_64line;
		des->reader = readFromBuff;
	}
	else
	{
		des->writer = writeToBuff;
		des->reader = readFromBuff;
	}
	return des;
}

void checkRsacmd(t_sslarg *arg, struct s_command *command)
{
	t_rsacmd *cmd;

	cmd = ft_memalloc(sizeof(t_rsacmd));
	ft_bzero(cmd, sizeof(t_rsacmd));
	allowOptions(arg, (char*[]){"in", "out", "pubin", "pubout", "passin", "passout", "des", "inform", "outform", "text", "noout", "check", "modulus", NULL});
	cmd->input = getContent(arg, "in");
	cmd->output = getContent(arg, "out");
	cmd->inform = getContent(arg, "inform");
	cmd->outform = getContent(arg, "outform");
	cmd->text = hasOption(arg, "text");
	cmd->noout = hasOption(arg, "noout");
	cmd->pubin = hasOption(arg, "pubin");
	cmd->pubout = hasOption(arg, "pubout");
	cmd->des = hasOption(arg, "des");
	cmd->check = hasOption(arg, "check");
	cmd->modulus = hasOption(arg, "modulus");
	cmd->desin = desForRsa(getContent(arg, "passin"), 1);
	cmd->desout = desForRsa(getContent(arg, "passout"), 0);
	if (cmd->inform && ft_strcmp(cmd->inform, "PEM") && ft_strcmp(cmd->inform, "DER"))
		basicError("inform possible value : PEM, DER");
	if (cmd->outform && ft_strcmp(cmd->outform, "PEM") && ft_strcmp(cmd->outform, "DER"))
		basicError("outform possible value : PEM, DER");
	if (cmd->check && cmd->pubin)
		basicError("Only private keys can be checked");
	if (cmd->input)
		fdReadAccess(cmd->input);
	if (cmd->output)
		fdWriteAccess(cmd->output);
	if (cmd->inform && !ft_strcmp(cmd->inform, "DER"))
		cmd->key = readKeyDER(cmd->pubin);
	else
		cmd->key = readKey(cmd->pubin, cmd->desin);
	command->param = cmd;
}

void freeRsacmd(t_rsacmd *cmd)
{
	ft_memdel((void**)&cmd->key);
	freeDES(cmd->desin);
	freeDES(cmd->desout);
	ft_memdel((void**)&cmd);
}

void executeRsacmd(struct s_command *command)
{
	t_rsacmd *cmd;

	cmd = command->param;
	if (cmd->check)
		checkRsaKey(cmd->key);
	if (cmd->text)
		printRsaKey(cmd->key);
	if (cmd->modulus)
		ft_printf("Modulus=%llX\n", cmd->key->modulus);
	if (!cmd->noout)
	{
		ft_printf("writing RSA key\n");
		if (cmd->outform && !ft_strcmp(cmd->outform, "DER"))
			writeKeyDER(cmd->key, cmd->pubout);
		else if (cmd->des)
			writeKey(cmd->key, cmd->pubout, cmd->desout);
		else
			writeKey(cmd->key, cmd->pubout, NULL);
	}
	freeRsacmd(cmd);
}
