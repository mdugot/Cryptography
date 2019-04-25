/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:19:14 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 17:23:45 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

const char	*g_standard[] = {
	"genrsa",
	"rsa",
	"rsautl",
	NULL
};

const char	*g_cypher[] = {
	"base64",
	"des",
	"des-ecb",
	"des-cbc",
	NULL
};

const char	*g_digest[] = {
	"md5",
	"sha256",
	NULL
};

int			is_in(char *str, const char *list[])
{
	int i;

	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strcmp(str, list[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void		print_list_command(char *name, const char *cmds[])
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

void		wrong_arg(t_sslarg *arg, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: [%s] %s\n", arg->command, message);
	exit(1);
}

void		basic_error(char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s\n", message);
	exit(1);
}

void		rsa_error(char *message)
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

void		wrong_file(char *filename, char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s: %s\n", filename, message);
	exit(1);
}

void		wrong_command(char *message)
{
	ft_printf_fd(2, "ft_ssl: Error: %s\n", message);
	print_list_command("Standard", (const char**)g_standard);
	print_list_command("Message Digest", (const char**)g_digest);
	print_list_command("Cypher", (const char**)g_cypher);
	exit(1);
}

void		check_command(t_sslarg *arg)
{
	if (arg->command == NULL)
		wrong_command("no command.");
	if (is_in(arg->command, (const char**)standard))
		return ;
	if (is_in(arg->command, (const char**)cypher))
		return ;
	if (is_in(arg->command, (const char**)digest))
		return ;
	wrong_command(ft_strf("'%s' is an invalid command.", arg->command));
}
