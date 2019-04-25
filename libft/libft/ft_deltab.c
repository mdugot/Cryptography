/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/31 17:09:34 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 17:00:42 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deltab(void *ad, size_t size)
{
	size_t	i;
	void	**tab;

	if (ad == NULL)
		return ;
	tab = (void**)ad;
	i = 0;
	while (i < size)
	{
		if (tab[i] != NULL)
			ft_memdel(&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab);
}
