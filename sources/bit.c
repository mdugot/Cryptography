/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:13:37 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 16:15:14 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit.h"

char	bit_mask(int idx)
{
	char	mask;
	int		i;

	i = 7;
	mask = 1;
	while (i > idx)
	{
		mask *= 2;
		i--;
	}
	return (mask);
}

void	set_bit(char *bytes, int idx, char bit)
{
	char mask;

	mask = bit_mask(idx % 8);
	idx = idx / 8;
	if (bit)
		bytes[idx] = bytes[idx] | mask;
	else
		bytes[idx] = bytes[idx] & (0xFF ^ mask);
}

char	get_bit(char *bytes, int idx)
{
	char mask;

	mask = bit_mask(idx % 8);
	idx = idx / 8;
	return ((bytes[idx] & mask) ? 1 : 0);
}
