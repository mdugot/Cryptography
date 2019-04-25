/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 15:30:33 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/16 19:48:44 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *str, char *to_delete, char *to_put)
{
	char	**split;
	char	*result;

	if (ft_strstr(str, to_delete) == NULL)
		return (str);
	split = ft_explode(str, to_delete);
	result = ft_implode(split, to_put);
	ft_strdel(&str);
	ft_deltab(split, ft_strsplit_size(split));
	return (result);
}
