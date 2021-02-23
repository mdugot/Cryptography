/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:13:28 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:23:59 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "command.h"

void	read_data(t_rsautl *cmd)
{
	size_t		len;
	char		buff;
	__uint64_t	data;

	data = 0;
	len = read_from_fd((char*)&data, 8);
	if (len == 8 && read_from_fd(&buff, 1) > 0)
		basic_error("data too large for key size");
	cmd->data = data;
	cmd->length = len;
}

void	get_content_rsautl(t_sslarg *arg, t_rsautl *cmd)
{
	cmd->input = get_content(arg, "in");
	cmd->output = get_content(arg, "out");
	cmd->inkey = get_content(arg, "inkey");
	cmd->pubin = has_option(arg, "pubin");
	cmd->decrypt = has_option(arg, "decrypt");
	cmd->hexdump = has_option(arg, "hexdump");
}

void	check_rsautl(t_sslarg *arg, struct s_command *command)
{
	t_rsautl *cmd;

	(void)arg;
	cmd = ft_memalloc(sizeof(t_rsautl));
	ft_bzero(cmd, sizeof(t_rsautl));
	allow_options(arg, (char*[]){"in", "out", \
			"pubin", "inkey", "encrypt", "decrypt", "hexdump", NULL});
	get_content_rsautl(arg, cmd);
	if (cmd->inkey == NULL)
		basic_error("no key file specified : \
				Use '-inkey FILE' to specify the key to use");
	if (cmd->decrypt && cmd->pubin)
		basic_error("decrypt mode need private key");
	if (cmd->output)
		fd_write_access(cmd->output);
	if (cmd->input)
		fd_read_access(cmd->input);
	read_data(cmd);
	fd_read_access(cmd->inkey);
	cmd->key = read_key(cmd->pubin, NULL);
	if (cmd->data > cmd->key->modulus)
		basic_error("data too large for key size");
	command->param = cmd;
}

void	free_rsautl(t_rsautl *cmd)
{
	ft_memdel((void**)&cmd);
}

void	execute_rsautl(struct s_command *command)
{
	t_rsautl	*cmd;
	__uint64_t	result;

	cmd = command->param;
	// print_rsa_key(cmd->key);
	if (cmd->decrypt)
		result = modular_pow(cmd->data, \
				cmd->key->private_exponent, cmd->key->modulus);
	else
		result = modular_pow(cmd->data, \
				cmd->key->public_exponent, cmd->key->modulus);
	if (cmd->hexdump)
		ft_printf("HEXDUMP : %08llX\n", result);
	write_to_fd((char*)&result, 8);
	free_rsautl(cmd);
}
