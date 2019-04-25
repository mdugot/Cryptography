/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 18:18:57 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/18 18:40:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorttab(int *tab, int size, int sens)
{
	int i;
	int tmp;

	if (size <= 1)
		return ;
	i = 1;
	while (i < size)
	{
		if ((sens >= 0 && tab[i] < tab[i - 1]) ||
			(sens < 0 && tab[i] > tab[i - 1]))
		{
			tmp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = tmp;
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

void	ft_sorttab_double(int *tab, int *tab2, int size, int sens)
{
	int i;
	int tmp;

	if (size <= 1)
		return ;
	i = 1;
	while (i < size)
	{
		if ((sens >= 0 && tab[i] < tab[i - 1]) ||
			(sens < 0 && tab[i] > tab[i - 1]))
		{
			tmp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = tmp;
			tmp = tab2[i];
			tab2[i] = tab2[i - 1];
			tab2[i - 1] = tmp;
			if (i > 1)
				i--;
		}
		else
			i++;
	}
}
