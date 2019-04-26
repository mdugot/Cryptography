/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:39:25 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:51:04 by mdugot           ###   ########.fr       */
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
	des->rsa = 0;
	des->password = get_content(arg, "p");
	des->input = get_content(arg, "i");
	des->output = get_content(arg, "o");
	des->key = get_content(arg, "k");
	des->salt = get_content(arg, "s");
	des->iv = get_content(arg, "v");
	des->decrypt = has_option(arg, "d");
	des->base_64 = has_option(arg, "a");
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

void				print_des(t_des *cmd, \
		unsigned long int code[3], int length, int last)
{
	char str_64[33] = {0};
	char endpad;

	endpad = 0;
	if (cmd->base_64 && !cmd->decrypt)
	{
		base_64_encode((char*)code, 8 * length, str_64);
		cmd->writer(str_64, ft_strlen(str_64));
	}
	else
	{
		if (last && cmd->decrypt)
		{
			endpad = (((char*)&code[length - 1])[7]);
		}
		cmd->writer((char*)code, 8 * length - endpad);
	}
}

size_t				read_des(t_des *cmd, char *buff)
{
	char buff_64[100];

	if (cmd->base_64 && cmd->decrypt)
		return (read_base_64(cmd->reader, buff, buff_64, 8));
	else
		return (cmd->reader(buff, 8));
}

unsigned long int	one_block_des(t_des *cmd, \
		unsigned long int buff, size_t length)
{
	unsigned long int code;

	code = des(buff, length, cmd);
	if (!cmd->decrypt)
		cmd->int_64_iv = code;
	else
		cmd->int_64_iv = buff;
	return (code);
}

unsigned int		print_magic(t_des *des, unsigned long int result[3])
{
	if (!des->rsa && des->generated_key && !des->decrypt)
	{
		ft_memcpy(&result[0], "Salted__", 8);
		ft_memcpy(&result[1], &des->int_64_salt, 8);
		return (2);
	}
	return (0);
}

void				des_command(t_des *cmd)
{
	size_t				length;
	unsigned long int	buff;
	unsigned long int	result[3];
	unsigned int		i;

	length = 8;
	i = print_magic(cmd, result);
	while (length >= 8)
	{
		length = read_des(cmd, (char*)&buff);
		if (!cmd->decrypt || length > 0 || i == 0)
		{
			if (i > 0 && i % 3 == 0)
				print_des(cmd, result, 3, 0);
			result[i % 3] = one_block_des(cmd, buff, length);
			i++;
		}
	}
	print_des(cmd, result, (i % 3 == 0 ? 3 : i % 3), 1);
}

void				execute_des(struct s_command *command)
{
	t_des *cmd;

	cmd = command->param;
	des_command(cmd);
	free_des(cmd);
	if (cmd->base_64 && !cmd->decrypt)
		cmd->writer("\n", 1);
}
