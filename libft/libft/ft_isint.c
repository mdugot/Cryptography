/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:14:11 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/24 16:14:53 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isint(char *s_int, int *result)
{
	int				i;
	int				r;
	long long int	tmp;

	i = 0;
	if (s_int[0] == 0)
		return (0);
	while (s_int[i])
	{
		if (!ft_isdigit(s_int[i]) &&
			!(s_int[i] == '-' && i == 0 && s_int[1]))
			return (0);
		i++;
	}
	tmp = ft_atol(s_int);
	r = (int)tmp;
	if ((long long int)r != tmp)
		return (0);
	*result = r;
	return (1);
}
