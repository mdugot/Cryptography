/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 18:24:40 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/21 18:35:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <time.h>

int		ft_random(int min, int max)
{
	int			rn;
	static int	first = 1;

	if (first)
	{
		first = 0;
		srand(time(NULL));
	}
	rn = min + rand() % (max - min + 1);
	return (rn);
}
