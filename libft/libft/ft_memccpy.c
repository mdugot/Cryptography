/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:06:38 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/25 12:51:17 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*src_temp;
	unsigned char		*dst_temp;

	i = 0;
	src_temp = (unsigned char*)src;
	dst_temp = (unsigned char*)dst;
	while (i < n)
	{
		dst_temp[i] = src_temp[i];
		if (src_temp[i] == (unsigned char)c)
			return (&(dst_temp[i + 1]));
		i++;
	}
	return (NULL);
}
