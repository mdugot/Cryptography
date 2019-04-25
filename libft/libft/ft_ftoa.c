/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 13:35:12 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/29 18:42:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ULLI	round_number(ULLI n)
{
	if (n % 10 >= 5)
		n += 10;
	n /= 10;
	return (n);
}

char	*ft_ftoa(double d, int precision)
{
	LLI		ent;
	ULLI	dec;
	char	*sdec;
	char	*sent;
	char	*result;

	ent = d;
	d -= ent;
	if (d < 0)
		d *= -1;
	while (precision-- >= 0 && (ULLI)(d * 10 + 10) > (ULLI)d)
		d *= 10;
	dec = round_number(d);
	sdec = ft_uitoa_base(dec, 10, 0);
	sent = ft_itoa_base(ent, 10);
	result = ft_strnew(ft_strlen(sdec) + ft_strlen(sent) + 2);
	ft_strcpy(result, sent);
	result[ft_strlen(result)] = '.';
	ft_strcat(result, sdec);
	ft_strdel(&sdec);
	ft_strdel(&sent);
	return (result);
}
