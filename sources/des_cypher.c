/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cypher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:52:55 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 16:48:01 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int	g_sbox[64 * 8] = {
	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, \
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, \
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, \
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13, \
	\
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, \
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, \
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, \
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9, \
	\
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, \
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, \
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, \
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12, \
	\
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, \
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, \
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, \
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14, \
	\
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, \
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, \
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, \
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3, \
	\
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, \
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, \
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, \
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13, \
	\
	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, \
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, \
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, \
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12, \
	\
	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, \
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, \
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, \
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

int	g_ftable[32] = {
	16, 7, 20, 21, \
	29, 12, 28, 17, \
	1, 15, 23, 26, \
	5, 18, 31, 10, \
	2, 8, 24, 14, \
	32, 27, 3, 9, \
	19, 13, 30, 6, \
	22, 11, 4, 25};

int	g_etable[64] = {
	32, 1, 2, 3, 4, 5, \
	4, 5, 6, 7, 8, 9, \
	8, 9, 10, 11, 12, 13, \
	12, 13, 14, 15, 16, 17, \
	16, 17, 18, 19, 20, 21, \
	20, 21, 22, 23, 24, 25, \
	24, 25, 26, 27, 28, 29, \
	28, 29, 30, 31, 32, 1};

int	g_ip_1[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, \
	39, 7, 47, 15, 55, 23, 63, 31, \
	38, 6, 46, 14, 54, 22, 62, 30, \
	37, 5, 45, 13, 53, 21, 61, 29, \
	36, 4, 44, 12, 52, 20, 60, 28, \
	35, 3, 43, 11, 51, 19, 59, 27, \
	34, 2, 42, 10, 50, 18, 58, 26, \
	33, 1, 41, 9, 49, 17, 57, 25};

int	g_ip[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, \
	60, 52, 44, 36, 28, 20, 12, 4, \
	62, 54, 46, 38, 30, 22, 14, 6, \
	64, 56, 48, 40, 32, 24, 16, 8, \
	57, 49, 41, 33, 25, 17, 9, 1, \
	59, 51, 43, 35, 27, 19, 11, 3, \
	61, 53, 45, 37, 29, 21, 13, 5, \
	63, 55, 47, 39, 31, 23, 15, 7};

int	g_pc1[56] = {
	57, 49, 41, 33, 25, 17, 9, \
	1, 58, 50, 42, 34, 26, 18, \
	10, 2, 59, 51, 43, 35, 27, \
	19, 11, 3, 60, 52, 44, 36, \
	63, 55, 47, 39, 31, 23, 15, \
	7, 62, 54, 46, 38, 30, 22, \
	14, 6, 61, 53, 45, 37, 29, \
	21, 13, 5, 28, 20, 12, 4};

int	g_pc2[56] = {
	14, 17, 11, 24, 1, 5, \
	3, 28, 15, 6, 21, 10, \
	23, 19, 12, 4, 26, 8, \
	16, 7, 27, 20, 13, 2, \
	41, 52, 31, 37, 47, 55, \
	30, 40, 51, 45, 33, 48, \
	44, 49, 39, 56, 34, 53, \
	46, 42, 50, 36, 29, 32};

int	g_shift[16] = {
	1, \
	1, \
	2, \
	2, \
	2, \
	2, \
	2, \
	2, \
	1, \
	2, \
	2, \
	2, \
	2, \
	2, \
	2, \
	1};

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
	permutation(cd, key, g_pc2, 48);
}

void				cd_16(char *pkey, char keys[16][6], char decrypt)
{
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
			set_bit(cd[i], j, get_bit(last, (j + g_shift[i]) % 28));
			j++;
		}
		j = 0;
		while (j < 28)
		{
			set_bit(cd[i], 28 + j, get_bit(last, 28 + (j + g_shift[i]) % 28));
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
	char	pkey[7];

	permutation((char*)&key, pkey, g_pc1, 56);
	cd_16(pkey, keys, decrypt);
}

int					get_sbox_value(char *bytes, int table, int offset)
{
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
	return (g_sbox[64 * table + y * 16 + x]);
}

int					fperm(int result)
{
	int presult;

	presult = 0;
	reverse_endian((char*)&result, 4);
	permutation((char*)&result, (char*)&presult, g_ftable, 32);
	return (presult);
}

int					function(char *right_half, char *key)
{
	char	tmp[6];
	int		i;
	int		box_value;
	int		result;

	permutation(right_half, tmp, g_etable, 48);
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
	unsigned long int	result;
	unsigned long int	presult;

	result = 0;
	ft_memcpy(&result, &r, 4);
	ft_memcpy(((char*)&result) + 4, &l, 4);
	permutation((char*)&result, (char*)&presult, g_ip_1, 64);
	return (presult);
}

unsigned long int	encode_message(unsigned long int message, \
		char keys[16][6])
{
	char	pmessage[8];
	int		i;
	int		r[17];
	int		l[17];

	(void)keys;
	permutation((char*)&message, pmessage, g_ip, 64);
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
