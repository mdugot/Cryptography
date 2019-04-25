/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:26:49 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/07 15:32:44 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *temp;

	temp = (char*)s;
	while (*temp != '\0')
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	if (c == '\0')
		return (temp);
	else
		return (NULL);
}

int		ft_index(const char *s, int c)
{
	char *temp;
	int r;

	r = 0;
	temp = (char*)s;
	while (*temp != '\0')
	{
		if (*temp == (char)c)
			return r;
		temp++;
		r++;
	}
	if (c == '\0')
		return r;
	else
		return -1;
}
