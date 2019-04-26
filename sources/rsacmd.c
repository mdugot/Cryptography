/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsacmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:06:02 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:12:28 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "command.h"

t_des	*des_for_rsa(char *password, int decrypt)
{
	t_des *des;

	des = ft_memalloc(sizeof(t_des));
	ft_bzero(des, sizeof(t_des));
	des->rsa = 1;
	des->cbc = 1;
	des->password = password;
	des->decrypt = decrypt;
	des->base_64 = 1;
	if (!decrypt)
	{
		des->writer = write_to_fd_64_line;
		des->reader = read_from_buff;
	}
	else
	{
		des->writer = write_to_buff;
		des->reader = read_from_buff;
	}
	return (des);
}

void	get_content_rsa(t_sslarg *arg, t_rsacmd *cmd)
{
	cmd->input = get_content(arg, "in");
	cmd->output = get_content(arg, "out");
	cmd->inform = get_content(arg, "inform");
	cmd->outform = get_content(arg, "outform");
	cmd->text = has_option(arg, "text");
	cmd->noout = has_option(arg, "noout");
	cmd->pubin = has_option(arg, "pubin");
	cmd->pubout = has_option(arg, "pubout");
	cmd->des = has_option(arg, "des");
	cmd->check = has_option(arg, "check");
	cmd->modulus = has_option(arg, "modulus");
	cmd->desin = des_for_rsa(get_content(arg, "passin"), 1);
	cmd->desout = des_for_rsa(get_content(arg, "passout"), 0);
}

void	check_rsacmd(t_sslarg *arg, struct s_command *command)
{
	t_rsacmd *cmd;

	cmd = ft_memalloc(sizeof(t_rsacmd));
	ft_bzero(cmd, sizeof(t_rsacmd));
	allow_options(arg, (char*[]){"in", "out", "pubin", "pubout", "passin", \
			"passout", "des", "inform", "outform", \
			"text", "noout", "check", "modulus", NULL});
	get_content_rsa(arg, cmd);
	if (cmd->inform &&
		ft_strcmp(cmd->inform, "PEM") && ft_strcmp(cmd->inform, "DER"))
		basic_error("inform possible value : PEM, DER");
	if (cmd->outform &&
		ft_strcmp(cmd->outform, "PEM") && ft_strcmp(cmd->outform, "DER"))
		basic_error("outform possible value : PEM, DER");
	if (cmd->check && cmd->pubin)
		basic_error("Only private keys can be checked");
	if (cmd->input)
		fd_read_access(cmd->input);
	if (cmd->output)
		fd_write_access(cmd->output);
	if (cmd->inform && !ft_strcmp(cmd->inform, "DER"))
		cmd->key = read_key_der(cmd->pubin);
	else
		cmd->key = read_key(cmd->pubin, cmd->desin);
	command->param = cmd;
}

void	free_rsacmd(t_rsacmd *cmd)
{
	ft_memdel((void**)&cmd->key);
	free_des(cmd->desin);
	free_des(cmd->desout);
	ft_memdel((void**)&cmd);
}

void	execute_rsacmd(struct s_command *command)
{
	t_rsacmd *cmd;

	cmd = command->param;
	if (cmd->check)
		check_rsa_key(cmd->key);
	if (cmd->text)
		print_rsa_key(cmd->key);
	if (cmd->modulus)
		ft_printf("Modulus=%llX\n", cmd->key->modulus);
	if (!cmd->noout)
	{
		ft_printf("writing RSA key\n");
		if (cmd->outform && !ft_strcmp(cmd->outform, "DER"))
			write_key_der(cmd->key, cmd->pubout);
		else if (cmd->des)
			write_key(cmd->key, cmd->pubout, cmd->desout);
		else
			write_key(cmd->key, cmd->pubout, NULL);
	}
	free_rsacmd(cmd);
}
