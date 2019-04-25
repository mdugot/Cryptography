#include "des.h"
#include "command.h"

void freeDES(t_des *des)
{
	ft_memdel((void**)&des);
}

void checkDES(t_sslarg *arg, struct s_command *command)
{
	t_des *des;

	des = ft_memalloc(sizeof(t_des));
	ft_bzero(des, sizeof(t_des));
	allowOptions(arg, (char*[]){"i", "o", "k", "d", "e", "a", "v", "s", "p", NULL});
	des->cbc = (ft_strcmp("des-ecb", command->name) != 0);
	des->rsa = 0;
	des->password = getContent(arg, "p");
	des->input = getContent(arg, "i");
	des->output = getContent(arg, "o");
	des->key = getContent(arg, "k");
	des->salt = getContent(arg, "s");
	des->iv = getContent(arg, "v");
	des->decrypt = hasOption(arg, "d");
	des->base64 = hasOption(arg, "a");
	if (des->base64 && !des->decrypt)
		des->writer = writeToFd_64line;
	else
		des->writer = writeToFd;
	des->reader = readFromFd;
	if (des->input)
		fdReadAccess(des->input);
	if (des->output)
		fdWriteAccess(des->output);
	if (arg->argc > 0)
		wrongArg(arg, ft_strf("unknown option '%s'", arg->argv[0]));
	desPassword(des);
	command->param = des;
}

void printDES(t_des *cmd, unsigned long int code[3], int length, int last)
{
	char str64[33] = {0};
	char endpad;

	endpad = 0;
	if (cmd->base64 && !cmd->decrypt)
	{
		base64encode((char*)code, 8*length, str64);
		cmd->writer(str64, ft_strlen(str64));
	}
	else
	{
		if (last && cmd->decrypt)
		{
			endpad = (((char*)&code[length-1])[7]);
		}
		cmd->writer((char*)code, 8*length-endpad);
	}
}

size_t readDES(t_des *cmd, char* buff)
{
	char buff64[100];

	if (cmd->base64 && cmd->decrypt)
		return readBase64(cmd->reader, buff, buff64, 8);
	else
		return cmd->reader(buff, 8);
}

unsigned long int oneBlockDES(t_des *cmd, unsigned long int buff, size_t length)
{
	unsigned long int code;

	code = des(buff, length, cmd);
	if (!cmd->decrypt)
		cmd->int64Iv = code;
	else
		cmd->int64Iv = buff;
	return code;
}

unsigned int printMagic(t_des *des, unsigned long int result[3])
{
	if (!des->rsa && des->generatedKey && !des->decrypt)
	{
		ft_memcpy(&result[0], "Salted__", 8);
		ft_memcpy(&result[1], &des->int64Salt, 8);
		return 2;
	}
	return 0;
}

void DES(t_des *cmd)
{
	size_t length;
	unsigned long int buff;
	unsigned long int result[3];
	unsigned int i;

	length = 8;
	i = printMagic(cmd, result);
	while (length >= 8)
	{
		length = readDES(cmd, (char*)&buff);
		if (!cmd->decrypt || length > 0 || i == 0)
		{
			if (i > 0 && i % 3 == 0)
				printDES(cmd, result, 3, 0);
			result[i % 3] = oneBlockDES(cmd, buff, length);
			i++;
		}
	}
	printDES(cmd, result, (i%3 == 0 ? 3 : i%3) , 1);
}

void executeDES(struct s_command *command)
{
	t_des *cmd;

	cmd = command->param;
	DES(cmd);
	freeDES(cmd);
	if (cmd->base64 && !cmd->decrypt)
		cmd->writer("\n", 1);
}
