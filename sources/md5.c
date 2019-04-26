/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:26:43 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:55:45 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "command.h"

static void				update(unsigned int *state, unsigned int *word)
{
	unsigned int r[64] = {OPERATIONS_TABLE};
	unsigned int k[64] = {ELEMENTS_TABLE};
	unsigned int i;
	unsigned int tmp[7];

	tmp[0] = state[0];
	tmp[1] = state[1];
	tmp[2] = state[2];
	tmp[3] = state[3];
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
		{
			tmp[4] = (tmp[1] & tmp[2]) | (~tmp[1] & tmp[3]);
			tmp[5] = i;
		}
		else if (i <= 31)
		{
			tmp[4] = (tmp[3] & tmp[1]) | (~tmp[3] & tmp[2]);
			tmp[5] = (5 * i + 1) % 16;
		}
		else if (i <= 47)
		{
			tmp[4] = tmp[1] ^ tmp[2] ^ tmp[3];
			tmp[5] = (3 * i + 5) % 16;
		}
		else
		{
			tmp[4] = tmp[2] ^ (tmp[1] | ~tmp[3]);
			tmp[5] = (7 * i) % 16;
		}
		tmp[6] = tmp[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = leftrotate((tmp[0] + tmp[4] + k[i] + word[tmp[5]]), \
				r[i]) + tmp[1];
		tmp[0] = tmp[6];
		i++;
	}
	state[0] += tmp[0];
	state[1] += tmp[1];
	state[2] += tmp[2];
	state[3] += tmp[3];
}

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
		update(state, (unsigned int*)&string[i * 64]);
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

static void				print_result(unsigned int *state, \
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

static unsigned int		*init_state(void)
{
	unsigned int	init[4] = {INIT_STATE};
	unsigned int	*state;
	size_t			size;

	size = sizeof(unsigned int) * 4;
	state = ft_memalloc(size);
	ft_memcpy(state, init, size);
	return (state);
}

void					execute_md5(struct s_command *command)
{
	execute_digest(command, md5, init_state, print_result);
}

unsigned int			*hash_md5(char *str)
{
	unsigned int *state;

	arg_read_access(str);
	state = hash(read_from_arg, md5, init_state, 0);
	return (state);
}
