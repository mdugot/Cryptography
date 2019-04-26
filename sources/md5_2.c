/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:53:50 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:59:57 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "command.h"

void					md5(char *string, unsigned int *state, \
		unsigned long int *size, size_t length)
{
	int nblock;
	int i;

	*size = *size + length;
	nblock = 1;
	if (length < 64)
	{
		string = pad(string, *size, &nblock, length);
	}
	i = 0;
	while (i < nblock)
	{
		md5_update(state, (unsigned int*)&string[i * 64]);
		i++;
	}
	if (length < 64)
		ft_memdel((void**)&string);
}

char					*md5_to_str(unsigned int *state)
{
	int		i;
	char	*bytes;

	i = 0;
	while (i < 4)
	{
		bytes = (char*)&state[i];
		reverse_endian(bytes, 4);
		i++;
	}
	return (ft_strf("%08x%08x%08x%08x", \
				state[0], state[1], state[2], state[3]));
}

void					md5_print_result(unsigned int *state, \
		char *string, char *file, t_digest *cmd)
{
	char *str;

	str = md5_to_str(state);
	if (cmd->quiet)
		ft_printf("%s\n", str);
	else if (cmd->reverse)
		rprint_hash(str, string, file, "MD5");
	else
		print_hash(str, string, file, "MD5");
	ft_strdel(&str);
	ft_memdel((void**)&state);
}

void					execute_md5(struct s_command *command)
{
	execute_digest(command, md5, md5_init_state, md5_print_result);
}

unsigned int			*hash_md5(char *str)
{
	unsigned int *state;

	arg_read_access(str);
	state = hash(read_from_arg, md5, md5_init_state, 0);
	return (state);
}
