/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:08:11 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 16:13:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "writer.h"
#include "reader.h"
#include "check.h"
#include "command.h"

void	free_64(t_base_64 *cmd)
{
	ft_memdel((void**)&cmd);
}

void	check_64(t_sslarg *arg, struct s_command *command)
{
	t_base_64 *cmd;

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

size_t	read_64(t_base64 *cmd, char *buff)
{
	char buff_64[BUFF64_SIZE * 2];

	if (cmd->decrypt)
		return (read_base_64(readFromFd, buff, buff_64, BUFF64_SIZE));
	else
		return (readFromFd(buff, BUFF64_SIZE));
}

void	print_64(t_base_64 *cmd, char *buff, size_t length)
{
	char str_64[BUFF64_SIZE * 2] = {0};

	if (!cmd->decrypt)
	{
		base_64_encode(buff, length, str_64);
		write_to_fd_64_line(str_64, ft_strlen(str_64));
	}
	else
	{
		write_to_fd(buff, length);
	}
}

void	execute_64(struct s_command *command)
{
	t_base64	*cmd;
	size_t		length;
	char		buff[BUFF64_SIZE];

	length = 1;
	cmd = command->param;
	while (length > 0)
	{
		length = read_64(cmd, buff);
		print_64(cmd, buff, length);
	}
	free_64(cmd);
}
