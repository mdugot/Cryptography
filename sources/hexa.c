/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:23:53 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 17:25:15 by mdugot           ###   ########.fr       */
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
