/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:19:14 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:39:36 by mdugot           ###   ########.fr       */
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
	if (is_in(arg->command, (const char**)g_standard))
		return ;
	if (is_in(arg->command, (const char**)g_cypher))
		return ;
	if (is_in(arg->command, (const char**)g_digest))
		return ;
	wrong_command(ft_strf("'%s' is an invalid command.", arg->command));
}
