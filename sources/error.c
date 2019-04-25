#include "error.h"

const char* standard[] = {
	"genrsa",
	"rsa",
	"rsautl",
	NULL
};

const char* cypher[] = {
	"base64",
	"des",
	"des-ecb",
	"des-cbc",
	NULL
};

const char* digest[] = {
	"md5",
	"sha256",
	NULL
};

int		isIn(char *str, const char *list[])
{
	int i;

	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strcmp(str, list[i]) == 0)
			return 1;
		i++;
	}
	return 0;
}

void printListCommand(char *name, const char *cmds[])
{
	int i;

	i = 0;
	ft_printf_fd(2, "\n%s commands:\n", name);
	while (cmds[i] != NULL)
	{
		ft_printf_fd(2, "%s\n", cmds[i]);
		i++;
	}
}

void wrongArg(t_sslarg *arg, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: [%s] %s\n", arg->command, message);
	exit(1);
}

void basicError(char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s\n", message);
	exit(1);
}

void rsaError(char *message)
{
	static int error = 0;

	if (message == NULL && error)
		exit(1);
	if (message)
	{
		ft_printf_fd(2, "RSA key error: %s\n", message);
		error = 1;
	}
}

void wrongFile(char *filename, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s: %s\n", filename, message);
	exit(1);
}

void wrongCommand(char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s\n", message);
	printListCommand("Standard", (const char**)standard);
	printListCommand("Message Digest", (const char**)digest);
	printListCommand("Cypher", (const char**)cypher);
	exit(1);
}

void checkCommand(t_sslarg *arg)
{
	if (arg->command == NULL)
		wrongCommand("no command.");
	if (isIn(arg->command, (const char**)standard))
		return ;
	if (isIn(arg->command, (const char**)cypher))
		return ;
	if (isIn(arg->command, (const char**)digest))
		return ;
	wrongCommand(ft_strf("'%s' is an invalid command.", arg->command));
}

