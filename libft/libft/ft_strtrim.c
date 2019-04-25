/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:06:59 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/26 17:22:48 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	len;
	char	*result;
	char	*temp;

	if (s == NULL)
		return (NULL);
	temp = (char*)s;
	while (is_whitespace(*temp))
		temp++;
	len = ft_strlen(temp);
	while (len > 0 && is_whitespace(temp[len - 1]))
		len--;
	result = ft_strnew(len);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, temp, len);
	return (result);
}
