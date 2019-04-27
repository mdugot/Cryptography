/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:35:01 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 20:28:33 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "command.h"

unsigned int g_sha_init[8] = {
	0x6a09e667, \
	0xbb67ae85, \
	0x3c6ef372, \
	0xa54ff53a, \
	0x510e527f, \
	0x9b05688c, \
	0x1f83d9ab, \
	0x5be0cd19};

static void				print_result(unsigned int *state, \
		char *string, char *file, t_digest *cmd)
{
	char *str;

	if (cmd->binary || cmd->colon)
		str = print_bytes_sha256(state, cmd);
	else
		str = ft_strf("%08x%08x%08x%08x%08x%08x%08x%08x",
			state[0], state[1], state[2], state[3],
			state[4], state[5], state[6], state[7]);
	if (cmd->binary)
		ft_printf("%s", str);
	else if (cmd->quiet)
		ft_printf("%s\n", str);
	else if (cmd->reverse)
		rprint_hash(str, string, file, "SHA256");
	else
		print_hash(str, string, file, "SHA256");
	ft_strdel(&str);
}

static unsigned int		*init_state(void)
{
	unsigned int	*state;
	size_t			size;

	size = sizeof(unsigned int) * 8;
	state = ft_memalloc(size);
	ft_memcpy(state, g_sha_init, size);
	return (state);
}

static void				update(unsigned int *state, unsigned int *word)
{
	unsigned int i;
	unsigned int w[64];
	unsigned int s[6];
	unsigned int tmp[8];

	ft_memcpy(tmp, state, sizeof(unsigned int) * 8);
	update_sha_1(word, w, s);
	update_sha_2(tmp, w, s);
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

void					execute_sha_256(struct s_command *command)
{
	execute_digest(command, sha_256, init_state, print_result);
}
