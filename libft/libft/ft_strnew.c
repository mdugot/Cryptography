/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:10:16 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/28 14:11:42 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *result;

	result = (char*)malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	ft_memset(result, '\0', size);
	return (result);
}
