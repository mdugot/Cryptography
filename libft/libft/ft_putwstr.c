/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 14:54:09 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/08 16:45:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putwstr_fd(unsigned int *str, int fd, char **result)
{
	while (*str)
	{
		ft_putwchar_fd(*str, fd, result);
		str++;
	}
}

void			ft_putwstr_size_fd(US *str, int fd, int size, char **result)
{
	int i;

	i = 0;
	while (*str && (i < size || size < 0))
	{
		ft_putwchar_fd(*str, fd, result);
		str++;
		i++;
	}
}
