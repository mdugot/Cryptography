/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:20:59 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:14:19 by mdugot           ###   ########.fr       */
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

unsigned int g_sha_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, \
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, \
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, \
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, \
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, \
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, \
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, \
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, \
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, \
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, \
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, \
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, \
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, \
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, \
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, \
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void				update(unsigned int *state, unsigned int *word)
{
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
		s[3] = tmp[7] + s[1] + s[2] + g_sha_k[i] + w[i];
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
	unsigned int	*state;
	size_t			size;

	size = sizeof(unsigned int) * 8;
	state = ft_memalloc(size);
	ft_memcpy(state, g_sha_init, size);
	return (state);
}

void					execute_sha_256(struct s_command *command)
{
	execute_digest(command, sha_256, init_state, print_result);
}
