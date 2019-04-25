/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 17:51:55 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/21 18:45:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_readstr(char *str)
{
	char	c;
	int		i;
	int		result;

	c = 0;
	i = 0;
	result = 1;
	while (c != '\n')
	{
		read(0, &c, 1);
		if (c == '\n' && str[i])
			result = 0;
		if (c != '\n' && result == 1 && str[i] != c)
			result = 0;
		i++;
	}
	if (i == 1)
		return (-1);
	return (result);
}
