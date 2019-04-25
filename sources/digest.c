#include "digest.h"
#include "command.h"

unsigned int* hash(size_t (*reader)(char*, size_t), void (*digest)(char*, unsigned int*, unsigned long int*, size_t), unsigned int* (*initState)(), int print)
{
	char buff[65];
	unsigned int *state;
	unsigned long int size;
	size_t length;

	state = initState();
	size = 0;
	length = reader(buff, 64);
	buff[length] = 0;
	if (print)
		ft_putstr(buff);
	digest(buff, state, &size, length);
	while (length >= 64)
	{
		length = reader(buff, 64);
		buff[length] = 0;
		if (print)
			ft_putstr(buff);
		digest(buff, state, &size, length);
	}
	return state;
}

void rprintHash(char* hash, char* string, char* file, char *type)
{
	(void)type;
	if (string)
		ft_printf("%s \"%s\"\n", hash, string);
	else if (file)
		ft_printf("%s %s\n", hash, file);
	else
		ft_printf("%s\n", hash);
}

void printHash(char* hash, char* string, char* file, char *type)
{
	if (string)
		ft_printf("%s (\"%s\") = %s\n", type, string, hash);
	else if (file)
		ft_printf("%s (%s) = %s\n", type, file, hash);
	else
		ft_printf("%s\n", hash);
}

void checkDigest(t_sslarg *arg, struct s_command *command)
{
	t_digest *digest;

	digest = ft_memalloc(sizeof(t_digest));
	allowOptions(arg, (char*[]){"p", "q", "r", "s", NULL});
	digest->string = getListContents(arg, "s");
	digest->reverse = hasOption(arg, "r");
	digest->quiet = hasOption(arg, "q");
	digest->printStdin = hasOption(arg, "p");
	digest->files = arg->argv;
	digest->nfiles = arg->argc;
	command->param = digest;
}

void freeDigest(t_digest *digest)
{
	if (digest->string)
		ft_memdel((void**)&(digest->string));
	ft_memdel((void**)&digest);
}

void executeDigest(struct s_command *command, void (*digest)(char*, unsigned int*, unsigned long int*, size_t), unsigned int* (*initState)(), void (*printResult)(unsigned int *, char*, char*, t_digest *))
{
	t_digest *cmd;
	int i;

	cmd = command->param;
	if ((!cmd->string && cmd->nfiles <= 0) || cmd->printStdin)
	{
		printResult(
			hash(readFromFd, digest, initState, cmd->printStdin),
			NULL, NULL, cmd);
	}
	if (cmd->string)
	{
		i = 0;
		while (cmd->string[i])
		{
			argReadAccess(cmd->string[i]);
			printResult(
				hash(readFromArg, digest, initState, 0),
				cmd->string[i], NULL, cmd);
			i++;
		}
	}
	i = 0;
	while (i < cmd->nfiles)
	{
		ft_printf("file : %s\n", cmd->files[i]);
		fdReadAccess(cmd->files[i]);
		printResult(
			hash(readFromFd, digest, initState, 0),
			NULL, cmd->files[i], cmd);
		i++;
	}
	freeDigest(cmd);
}
