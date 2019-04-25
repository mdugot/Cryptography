/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   significant_bit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:09:12 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/18 14:44:37 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	significant_bit(void *p, size_t size)
{
	int				result;
	unsigned char	mask;
	size_t			i;
	int				j;
	unsigned char	*ad;

	i = 0;
	result = 0;
	ad = p + size - 1;
	while (i < size)
	{
		mask = 0x80;
		j = -1;
		while (++j < 8)
		{
			if (!(mask & *ad))
				result++;
			else
				return (size * 8 - result);
			mask = mask >> 1;
		}
		i++;
		ad--;
	}
	return (0);
}
