/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:45:31 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 15:19:34 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "command.h"

void				free_des(t_des *des)
{
	ft_memdel((void**)&des);
}

void				check_des(t_sslarg *arg, struct s_command *command)
{
	t_des *des;

	des = ft_memalloc(sizeof(t_des));
	ft_bzero(des, sizeof(t_des));
	allow_options(arg, \
			(char*[]){"i", "o", "k", "d", "e", "a", "v", "s", "p", NULL});
	des->cbc = (ft_strcmp("des-ecb", command->name) != 0);
	get_content_des(arg, des);
	if (des->base_64 && !des->decrypt)
		des->writer = write_to_fd_64_line;
	else
		des->writer = write_to_fd;
	des->reader = read_from_fd;
	if (des->input)
		fd_read_access(des->input);
	if (des->output)
		fd_write_access(des->output);
	if (arg->argc > 0)
		wrong_arg(arg, ft_strf("unknown option '%s'", arg->argv[0]));
	des_password(des);
	command->param = des;
}

size_t				read_des(t_des *cmd, char *buff)
{
	char buff_64[100];

	if (cmd->base_64 && cmd->decrypt)
		return (read_base_64(cmd->reader, buff, buff_64, 8));
	else
		return (cmd->reader(buff, 8));
}

void				execute_des(struct s_command *command)
{
	t_des *cmd;

	cmd = command->param;
	des_command(cmd);
	if (cmd->base_64 && !cmd->decrypt)
		cmd->writer("\n", 1);
	free_des(cmd);
}
