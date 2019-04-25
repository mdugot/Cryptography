#include "base64.h"
#include "writer.h"
#include "reader.h"
#include "check.h"
#include "command.h"

void free64(t_base64 *cmd)
{
	ft_memdel((void**)&cmd);
}

void check64(t_sslarg *arg, struct s_command *command)
{
	t_base64 *cmd;

	cmd = ft_memalloc(sizeof(t_base64));
	ft_bzero(cmd, sizeof(t_base64));
	allowOptions(arg, (char*[]){"i", "o", "d", "e", NULL});
	cmd->input = getContent(arg, "i");
	cmd->output = getContent(arg, "o");
	cmd->decrypt = hasOption(arg, "d");
	if (cmd->input)
		fdReadAccess(cmd->input);
	if (cmd->output)
		fdWriteAccess(cmd->output);
	if (arg->argc > 0)
		wrongArg(arg, ft_strf("unknown option '%s'", arg->argv[0]));
	command->param = cmd;
}

size_t read64(t_base64 *cmd, char* buff)
{
	char buff64[BUFF64_SIZE * 2];

	if (cmd->decrypt)
		return readBase64(readFromFd, buff, buff64, BUFF64_SIZE);
	else
		return readFromFd(buff, BUFF64_SIZE);
}

void print64(t_base64 *cmd, char *buff, size_t length)
{
	char str64[BUFF64_SIZE * 2] = {0};

	if (!cmd->decrypt)
	{
		base64encode(buff, length, str64);
		writeToFd_64line(str64, ft_strlen(str64));
	}
	else
	{
		writeToFd(buff, length);
	}
}

void execute64(struct s_command *command)
{
	t_base64 *cmd;
	size_t length;
	char buff[BUFF64_SIZE];

	length = 1;
	cmd = command->param;
	while (length > 0)
	{
		length = read64(cmd, buff);
		print64(cmd, buff, length);
	}
	free64(cmd);
}
