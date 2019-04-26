/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cypher2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:15:32 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:18:59 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

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
