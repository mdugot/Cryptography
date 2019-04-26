/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:24:29 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:41:07 by mdugot           ###   ########.fr       */
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

char	*ft_first_of(const char *bytes, const char *one_of, size_t n)
{
	int		i;
	char	*found;

	i = 0;
	while (one_of[i])
	{
		found = ft_memchr(bytes, (int)one_of[i], n);
		if (found)
			return (found);
		i++;
	}
	return (NULL);
}
