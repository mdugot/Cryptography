/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cypher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:52:55 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:54:21 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void				permutation(char *from, char *to, \
		int *permutation_table, int length)
{
	int i;
	int pi;

	i = 0;
	while (i < length)
	{
		pi = permutation_table[i] - 1;
		set_bit(to, i, get_bit(from, pi));
		i++;
	}
}

void				print_bits(char *message, char *bytes, int length)
{
	int i;

	i = 0;
	ft_printf("%s :", message);
	while (i < length)
	{
		ft_printf(" %08hhb", bytes[i]);
		i++;
	}
	ft_putendl("");
}

void				subkey(char *key, char *cd)
{
	int pc2[56] = {PC2};

	permutation(cd, key, pc2, 48);
}

void				cd_16(char *pkey, char keys[16][6], char decrypt)
{
	int		shift[16] = {CD16_SHIFT};
	char	cd[16][7];
	char	*last;
	int		i;
	int		j;

	last = pkey;
	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 28)
		{
			set_bit(cd[i], j, get_bit(last, (j + shift[i]) % 28));
			j++;
		}
		j = 0;
		while (j < 28)
		{
			set_bit(cd[i], 28 + j, get_bit(last, 28 + (j + shift[i]) % 28));
			j++;
		}
		last = cd[i];
		subkey(keys[(decrypt ? (15 - i) : i)], cd[i]);
		i++;
	}
}

void				prepare_keys(unsigned long int key, \
		char keys[16][6], char decrypt)
{
	int		pc1[56] = {PC1};
	char	pkey[7];

	permutation((char*)&key, pkey, pc1, 56);
	cd_16(pkey, keys, decrypt);
}

int					get_sbox_value(char *bytes, int table, int offset)
{
	int		sbox[64 * 8] = {SBOX};
	char	x;
	char	y;

	x = 0;
	y = 0;
	set_bit(&y, 6, get_bit(bytes, offset));
	set_bit(&y, 7, get_bit(bytes, offset + 5));
	set_bit(&x, 4, get_bit(bytes, offset + 1));
	set_bit(&x, 5, get_bit(bytes, offset + 2));
	set_bit(&x, 6, get_bit(bytes, offset + 3));
	set_bit(&x, 7, get_bit(bytes, offset + 4));
	return (sbox[64 * table + y * 16 + x]);
}

int					fperm(int result)
{
	int ftable[32] = {FTABLE};
	int presult;

	presult = 0;
	reverse_endian((char*)&result, 4);
	permutation((char*)&result, (char*)&presult, ftable, 32);
	return (presult);
}

int					function(char *right_half, char *key)
{
	char	tmp[6];
	int		etable[64] = {ETABLE};
	int		i;
	int		box_value;
	int		result;

	permutation(right_half, tmp, etable, 48);
	i = 0;
	while (i < 6)
	{
		tmp[i] = tmp[i] ^ key[i];
		i++;
	}
	i = 0;
	result = 0;
	while (i < 8)
	{
		box_value = get_sbox_value(tmp, i, i * 6);
		result = (result << 4) | box_value;
		i++;
	}
	return (fperm(result));
}

unsigned long int	merge_lr(int l, int r)
{
	int					ip_1[64] = {IP_1};
	unsigned long int	result;
	unsigned long int	presult;

	result = 0;
	ft_memcpy(&result, &r, 4);
	ft_memcpy(((char*)&result) + 4, &l, 4);
	permutation((char*)&result, (char*)&presult, ip_1, 64);
	return (presult);
}

unsigned long int	encode_message(unsigned long int message, \
		char keys[16][6])
{
	char	pmessage[8];
	int		ip[64] = {IP};
	int		i;
	int		r[17];
	int		l[17];

	(void)keys;
	permutation((char*)&message, pmessage, ip, 64);
	ft_memcpy(&r[0], pmessage + 4, 4);
	ft_memcpy(&l[0], pmessage, 4);
	i = 1;
	while (i < 17)
	{
		r[i] = l[i - 1] ^ function((char*)&r[i - 1], keys[i - 1]);
		l[i] = r[i - 1];
		i++;
	}
	return (merge_lr(l[16], r[16]));
}

unsigned long int	des(unsigned long int message, \
		size_t length, t_des *cmd)
{
	unsigned long int	result;
	char				keys[16][6];

	if (!cmd->decrypt && length < 8)
		pkcs((char*)&message, 8, length);
	if (!cmd->decrypt && cmd->cbc)
		message = message ^ cmd->int_64_iv;
	prepare_keys(cmd->int_64_key, keys, cmd->decrypt);
	result = encode_message(message, keys);
	if (cmd->decrypt && cmd->cbc)
		result = result ^ cmd->int_64_iv;
	return (result);
}
