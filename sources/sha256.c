/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:20:59 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 20:31:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "command.h"

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

void				update_sha_1(unsigned int *word, \
		unsigned int *w, unsigned int *s)
{
	unsigned int i;

	i = 0;
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
}

void				update_sha_2(unsigned int *tmp, \
		unsigned int *w, unsigned int *s)
{
	unsigned int i;

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
}

char				*print_bytes_sha256(unsigned int *state, t_digest *cmd)
{
	char	*str;
	char	bytes[100];
	int		i;

	ft_bzero(bytes, 100);
	i = 0;
	while (i < 8)
	{
		reverse_endian((char*)&state[i], sizeof(unsigned int));
		i++;
	}
	ft_memcpy((void*)bytes, (void*)state, 8 * sizeof(unsigned int));
	if (cmd->binary)
		str = ft_strf("%.*s", 8 * sizeof(unsigned int), bytes);
	else
		str = colons_hexa(bytes, 8 * sizeof(unsigned int));
	return (str);
}
