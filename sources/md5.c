/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:26:43 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 16:39:21 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "command.h"

unsigned int g_md5_k[64] = {
	3614090360, 3905402710, 606105819, 3250441966, \
	4118548399, 1200080426, 2821735955, 4249261313, \
	1770035416, 2336552879, 4294925233, 2304563134, \
	1804603682, 4254626195, 2792965006, 1236535329, \
	4129170786, 3225465664, 643717713, 3921069994, \
	3593408605, 38016083, 3634488961, 3889429448, \
	568446438, 3275163606, 4107603335, 1163531501, \
	2850285829, 4243563512, 1735328473, 2368359562, \
	4294588738, 2272392833, 1839030562, 4259657740, \
	2763975236, 1272893353, 4139469664, 3200236656, \
	681279174, 3936430074, 3572445317, 76029189, \
	3654602809, 3873151461, 530742520, 3299628645, \
	4096336452, 1126891415, 2878612391, 4237533241, \
	1700485571, 2399980690, 4293915773, 2240044497, \
	1873313359, 4264355552, 2734768916, 1309151649, \
	4149444226, 3174756917, 718787259, 3951481745};

unsigned int g_md5_r[64] = {
	7, 12, 17, 22, \
	7, 12, 17, 22, \
	7, 12, 17, 22, \
	7, 12, 17, 22, \
	5, 9, 14, 20, \
	5, 9, 14, 20, \
	5, 9, 14, 20, \
	5, 9, 14, 20, \
	4, 11, 16, 23, \
	4, 11, 16, 23, \
	4, 11, 16, 23, \
	4, 11, 16, 23, \
	6, 10, 15, 21, \
	6, 10, 15, 21, \
	6, 10, 15, 21, \
	6, 10, 15, 21};

unsigned int g_md5_init[4] = {
	0x67452301, \
	0xEFCDAB89, \
	0x98BADCFE, \
	0x10325476};

static void				update(unsigned int *state, unsigned int *word)
{
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
		tmp[1] = leftrotate((tmp[0] + tmp[4] + g_md5_k[i] + word[tmp[5]]), \
				g_md5_r[i]) + tmp[1];
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
	unsigned int	*state;
	size_t			size;

	size = sizeof(unsigned int) * 4;
	state = ft_memalloc(size);
	ft_memcpy(state, g_md5_init, size);
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
