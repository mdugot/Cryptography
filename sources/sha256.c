/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:20:59 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:30:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "command.h"

static void				update(unsigned int *state, unsigned int *word)
{
	unsigned int k[64] = {CONSTANTS_SHA256};
	unsigned int i;
	unsigned int w[64];
	unsigned int s[6];
	unsigned int tmp[8];

	i = 0;
	ft_memcpy(tmp, state, 32 * 8);
	while (i < 64)
	{
		if (i <= 15)
		{
			w[i] = word[i];
			reverse_endian((char*)&w[i], 4);
		}
		else
		{
			s[0] = rightrotate(w[i - 15], 7) ^ \
				rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
			s[1] = rightrotate(\
					w[i - 2], 17) ^ \
				rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + s[0] + w[i - 7] + s[1];
		}
		i++;
	}
	i = 0;
	while (i < 64)
	{
		s[1] = rightrotate(\
				tmp[4], 6) ^ rightrotate(tmp[4], 11) ^ rightrotate(tmp[4], 25);
		s[2] = (tmp[4] & tmp[5]) ^ ((~tmp[4]) & tmp[6]);
		s[3] = tmp[7] + s[1] + s[2] + k[i] + w[i];
		s[0] = rightrotate(\
				tmp[0], 2) ^ rightrotate(tmp[0], 13) ^ rightrotate(tmp[0], 22);
		s[4] = (tmp[0] & tmp[1]) ^ (tmp[0] & tmp[2]) ^ (tmp[1] & tmp[2]);
		s[5] = s[0] + s[4];
		tmp[7] = tmp[6];
		tmp[6] = tmp[5];
		tmp[5] = tmp[4];
		tmp[4] = tmp[3] + s[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = tmp[0];
		tmp[0] = s[3] + s[5];
		i++;
	}
	i = 0;
	while (i < 8)
	{
		state[i] += tmp[i];
		i++;
	}
}

void					sha_256(char *string, \
		unsigned int *state, unsigned long int *size, size_t length)
{
	int nblock;
	int i;

	*size = *size + length;
	nblock = 1;
	if (length < 64)
	{
		string = pad(string, *size, &nblock, length);
		reverse_endian(string + (nblock - 1) * 64 + 56, 8);
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

static void				print_result(unsigned int *state, \
		char *string, char *file, t_digest *cmd)
{
	char *str;

	str = ft_strf("%08x%08x%08x%08x%08x%08x%08x%08x",
		state[0], state[1], state[2], state[3],
		state[4], state[5], state[6], state[7]);
	if (cmd->quiet)
		ft_printf("%s\n", str);
	else if (cmd->reverse)
		rprint_hash(str, string, file, "SHA256");
	else
		print_hash(str, string, file, "SHA256");
	ft_strdel(&str);
	ft_memdel((void**)&state);
}

static unsigned int		*init_state(void)
{
	unsigned int	init[8] = {STATE_SHA256};
	unsigned int	*state;
	size_t			size;

	size = sizeof(unsigned int) * 8;
	state = ft_memalloc(size);
	ft_memcpy(state, init, size);
	return (state);
}

void					execute_sha_256(struct s_command *command)
{
	execute_digest(command, sha_256, init_state, print_result);
}
