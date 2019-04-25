/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tab_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:49:49 by mressier          #+#    #+#             */
/*   Updated: 2016/03/31 17:13:51 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_str_tab_del(char ***str)
{
	int		indx;

	indx = 0;
	while (*str && (*str)[indx])
	{
		ft_strdel(&((*str)[indx]));
		indx++;
	}
	ft_memdel((void **)str);
}
