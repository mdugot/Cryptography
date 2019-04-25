/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:09:22 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/25 18:27:18 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	result = ft_strnew(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < (unsigned int)len)
	{
		result[i] = s[start + i];
		i++;
	}
	return (result);
}
