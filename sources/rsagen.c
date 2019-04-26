/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsagen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:11:27 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:13:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "command.h"

void	check_rsagen(t_sslarg *arg, struct s_command *command)
{
	t_rsagen *cmd;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_rsagen));
	ft_bzero(cmd, sizeof(t_rsagen));
	allow_options(arg, (char*[]){"o", "rand", NULL});
	cmd->output = get_content(arg, "o");
	if (cmd->output)
		fd_write_access(cmd->output);
	cmd->random = get_content(arg, "rand");
	if (cmd->random)
		random_read(NULL, 0, cmd->random);
	command->param = cmd;
}

void	free_rsagen(t_rsagen *cmd)
{
	ft_memdel((void**)&cmd);
}

void	execute_rsagen(struct s_command *command)
{
	t_rsagen *cmd;
	t_rsakey *key;

	cmd = command->param;
	key = create_rsa_key(ft_ssl_is_primary, 0.9999999);
	write_key(key, 0, NULL);
	free_rsagen(cmd);
}
