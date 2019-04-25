/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 10:30:41 by exam              #+#    #+#             */
/*   Updated: 2016/01/18 14:05:38 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			find_size(uintmax_t value, int base, int sign)
{
	size_t result;

	result = 0;
	if (sign == -1)
		result = 1;
	while (value > 0)
	{
		result++;
		value /= base;
	}
	return (result);
}

void			fill_nbr(char *str, uintmax_t value, int base, size_t size)
{
	char	*nbr;
	int		n;

	nbr = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (value > 0)
	{
		n = value % (uintmax_t)base;
		value /= (uintmax_t)base;
		size--;
		str[size] = nbr[n];
	}
}

char			*zero(void)
{
	char *result;

	result = ft_memalloc(sizeof(char) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

char			*ft_itoa_base(intmax_t value, int base)
{
	int				sign;
	uintmax_t		u_value;
	char			*result;
	size_t			size;

	if (base < 2 || base > 36)
		return (NULL);
	if (value == 0)
		return (zero());
	result = NULL;
	sign = 1;
	if (value < 0)
		sign = -1;
	u_value = value * (value < 0 ? -1 : 1);
	size = find_size(u_value, base, sign);
	result = ft_memalloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	if (sign == -1)
		result[0] = '-';
	fill_nbr(result, u_value, base, size);
	return (result);
}

char			*ft_uitoa_base(uintmax_t u_value, int base, int up)
{
	char			*result;
	size_t			size;

	if (base < 2 || base > 36)
		return (NULL);
	if (u_value == 0)
		return (zero());
	result = NULL;
	size = find_size(u_value, base, 1);
	result = ft_memalloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	fill_nbr(result, u_value, base, size);
	if (!up)
		ft_strlower(result);
	return (result);
}
