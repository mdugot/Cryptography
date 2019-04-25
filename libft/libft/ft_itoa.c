/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:40:32 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/09 13:32:49 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		calculate_size_abs(long long n)
{
	int size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void		fill_with_number(char *str, long long n, int i)
{
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

static int		find_size(int len, long long n)
{
	if (n < 0)
		return (len + 2);
	else
		return (len + 1);
}

char			*ft_itoa(int n)
{
	int			len;
	int			i;
	char		*result;
	long long	temp;

	temp = (long long)n;
	len = calculate_size_abs(temp);
	result = ft_strnew(find_size(len, temp));
	if (result == NULL)
		return (NULL);
	if (temp < 0)
	{
		temp *= -1;
		result[0] = '-';
		i = len;
	}
	else
		i = len - 1;
	if (temp == 0)
		result[0] = '0';
	else
		fill_with_number(result, temp, i);
	return (result);
}
