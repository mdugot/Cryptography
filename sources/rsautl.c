#include "rsa.h"
#include "command.h"

void readData(t_rsautl *cmd)
{
	size_t len;
	char buff;
	__uint64_t data;

	data = 0;
	len = readFromFd((char*)&data, 8);
	if (len == 8 && readFromFd(&buff, 1) > 0)
		basicError("data too large for key size");
//	ft_printf("HEXDUMP : %08llX\n", data);
	cmd->data = data;
	cmd->length = len;
}

void checkRsautl(t_sslarg *arg, struct s_command *command)
{
	t_rsautl *cmd;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_rsautl));
	ft_bzero(cmd, sizeof(t_rsautl));
	allowOptions(arg, (char*[]){"in", "out", "pubin", "inkey", "encrypt", "decrypt", "hexdump", NULL});
	cmd->input = getContent(arg, "in");
	cmd->output = getContent(arg, "out");
	cmd->inkey = getContent(arg, "inkey");
	cmd->pubin = hasOption(arg, "pubin");
	cmd->decrypt = hasOption(arg, "decrypt");
	cmd->hexdump = hasOption(arg, "hexdump");
	if (cmd->inkey == NULL)
		basicError("no key file specified : Use '-inkey FILE' to specify the key to use");
	if (cmd->decrypt && cmd->pubin)
		basicError("decrypt mode need private key");
	if (cmd->output)
		fdWriteAccess(cmd->output);
	if (cmd->input)
		fdReadAccess(cmd->input);
	readData(cmd);
	fdReadAccess(cmd->inkey);
	cmd->key = readKey(cmd->pubin, NULL);
	if (cmd->data > cmd->key->modulus)
		basicError("data too large for key size");
	command->param = cmd;
}

void freeRsautl(t_rsautl *cmd)
{
	ft_memdel((void**)&cmd);
}

void executeRsautl(struct s_command *command)
{
	t_rsautl *cmd;
	__uint64_t result;

	cmd = command->param;
	printRsaKey(cmd->key);
	if (cmd->decrypt)
		result = modularPow(cmd->data, cmd->key->privateExponent, cmd->key->modulus);
	else
		result = modularPow(cmd->data, cmd->key->publicExponent, cmd->key->modulus);
	if (cmd->hexdump)
		ft_printf("HEXDUMP : %08llX\n", result);
	writeToFd((char*)&result, 8);
	freeRsautl(cmd);
}
