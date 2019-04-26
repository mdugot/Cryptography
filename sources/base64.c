/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:03:30 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:09:00 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

char	g_codes[] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"\
	"abcdefghijklmnopqrstuvwxyz"\
	"0123456789+/"};

char	get_6_bits(char *bits, int length, int offset)
{
	int		i;
	char	value;

	i = 0;
	value = 0;
	if (length >= 6)
		length = 6;
	while (i < length)
	{
		set_bit(&value, 2 + i, get_bit(bits, offset + i));
		i++;
	}
	return (g_codes[(int)value]);
}

void	base_64_encode(char *from, size_t length, char *to)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < length * 8)
	{
		to[j] = get_6_bits(from, length * 8 - i, i);
		i += 6;
		j++;
	}
	while (j % 4 > 0)
	{
		to[j] = '=';
		j++;
	}
}

void	set_6_bits(char *to, size_t n, size_t offset, char c)
{
	char	value;
	size_t	i;

	value = ft_index(g_codes, (int)c);
	if (value < 0)
		basic_error("wrong character during base64 decoding");
	i = 0;
	if (n > 6)
		n = 6;
	while (i < n)
	{
		set_bit(to, offset + i, get_bit(&value, 2 + i));
		i++;
	}
}

size_t	base_64_decode(char *from, size_t length, char *to)
{
	size_t padding;
	size_t i;

	padding = 0;
	if (length > 1 && from[length - 1] == '=')
		padding++;
	if (length > 2 && from[length - 2] == '=')
		padding++;
	i = 0;
	while (i < length - padding)
	{
		if (i == length - padding - 1 && padding == 1)
			set_6_bits(to, 4, i * 6, from[i]);
		if (i == length - padding - 1 && padding == 2)
			set_6_bits(to, 2, i * 6, from[i]);
		else
			set_6_bits(to, 6, i * 6, from[i]);
		i++;
	}
	return (div_ceil(length, 4) * 3 - padding);
}
