/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:23:53 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 20:32:23 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hexa.h"

unsigned long int	key_from_string(char *str)
{
	unsigned long int	result;
	int					pad;

	if (ft_strlen(str) > 16)
		str[16] = 0;
	ft_strupper(str);
	result = ft_hexa(str);
	pad = 0;
	while (ft_strlen(str) + pad < 16)
	{
		result *= 16;
		pad++;
	}
	reverse_endian((char*)&result, 8);
	return (result);
}

char				*colons_hexa(char *bytes, size_t len)
{
	char	*result;
	size_t	i;
	char	*tmp;

	result = ft_strnew(len * 3 + 1);
	result[0] = 0;
	tmp = ft_strf("%02hhx", bytes[0]);
	ft_strcat(result, tmp);
	ft_strdel(&tmp);
	i = 1;
	while (i < len)
	{
		tmp = ft_strf(":%02hhx", bytes[i]);
		ft_strcat(result, tmp);
		ft_strdel(&tmp);
		i++;
	}
	return (result);
}
