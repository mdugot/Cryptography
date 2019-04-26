/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:14:03 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 14:19:19 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "padding.h"

char			*pad(char *string, long unsigned int size, \
		int *nblock, size_t length)
{
	long unsigned int	bits_len;
	long unsigned int	nbits;
	char				*result;

	size = size * 8;
	bits_len = 8 * length;
	nbits = bits_len;
	if (nbits < 448)
	{
		*nblock = 1;
		nbits += 448 - nbits;
	}
	else
	{
		*nblock = 2;
		nbits += 448 + (512 - nbits);
	}
	nbits += 64;
	result = ft_memalloc((nbits / 8));
	ft_bzero(result, (nbits / 8));
	ft_memcpy(result, string, length);
	result[length] = 0x80;
	ft_memcpy((void*)&result[(nbits / 8) - 8], (void*)&size, 8);
	return (result);
}

void			pkcs(char *bytes, size_t block_size, size_t length)
{
	char fill;
	char i;

	fill = block_size - length;
	i = 0;
	while (i < fill)
	{
		bytes[length + i] = fill;
		i++;
	}
}

unsigned int	leftrotate(unsigned int value, unsigned int shift)
{
	return ((value << shift) | (value >> (32 - shift)));
}

unsigned int	rightrotate(unsigned int value, unsigned int shift)
{
	return ((value >> shift) | (value << (32 - shift)));
}

void			reverse_endian(char *bytes, int length)
{
	char	tmp;
	int		i;

	i = 0;
	while (i < length / 2)
	{
		tmp = bytes[i];
		bytes[i] = bytes[length - (i + 1)];
		bytes[length - (i + 1)] = tmp;
		i++;
	}
}
