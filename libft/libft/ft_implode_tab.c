/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:14:31 by udelorme          #+#    #+#             */
/*   Updated: 2016/04/26 13:22:58 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_implode_tab(char **data, int start, size_t len)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = start;
	ret = ft_strdup(data[i++]);
	while (data[i] && (start + i) < (int)len)
	{
		tmp = ft_strjoin(ret, data[i]);
		free(ret);
		ret = tmp;
		i++;
	}
	return (ret);
}
