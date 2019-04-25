/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 09:41:42 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/25 12:54:27 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dst_temp;
	char		*src_temp;

	dst_temp = (char*)dst;
	src_temp = (char*)src;
	i = 0;
	if (src < dst && len > 0)
	{
		i = (len - 1);
		while (i > 0)
		{
			dst_temp[i] = src_temp[i];
			i--;
		}
		dst_temp[i] = src_temp[i];
	}
	else
		while (i < len)
		{
			dst_temp[i] = src_temp[i];
			i++;
		}
	return (dst);
}
