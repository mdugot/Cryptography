/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:24:29 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/25 11:06:18 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	c_temp;
	unsigned char	*s_temp;

	i = 0;
	c_temp = (unsigned char)c;
	s_temp = (unsigned char*)s;
	while (i < n)
	{
		if (c_temp == s_temp[i])
			return (&(s_temp[i]));
		i++;
	}
	return (NULL);
}

char	*ft_firstOf(const char *bytes, const char *oneOf, size_t n)
{
	int i;
	char *found;

	i = 0;
	while (oneOf[i])
	{
		found = ft_memchr(bytes, (int)oneOf[i], n);
		if (found)
			return (found);
		i++;
	}
	return (NULL);
}
