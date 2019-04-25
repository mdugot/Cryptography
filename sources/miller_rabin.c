/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miller_rabin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:38:23 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 17:44:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miller_rabin.h"
#include "error.h"

int	witness(__uint64_t a, __uint64_t n)
{
	__uint64_t m;
	__uint64_t y;
	__uint64_t b;

	m = n - 1;
	y = 1;
	while (m != 0)
	{
		if (m % 2 == 1)
		{
			y = (a * y) % n;
			m = m - 1;
		}
		else
		{
			b = a;
			a = (a * a) % n;
			if (a == 1 && b != 1 && b != n - 1)
				return (1);
			m = m / 2;
		}
	}
	if (y != 1)
		return (1);
	else
		return (0);
}

int	miller_witness(__uint64_t base, __uint64_t number)
{
	__uint64_t s;
	__uint64_t d;
	__uint64_t x;

	d = number - 1;
	s = 0;
	while (d % 2 == 0)
	{
		s++;
		d /= 2;
	}
	x = modular_pow(base, d, number);
	if (x == base || x == number - 1)
	{
		return (0);
	}
	while (s > 1)
	{
		x = modular_pow(x, 2, number);
		if (x == (number - 1))
		{
			return (0);
		}
		s = s - 1;
	}
	return (1);
}

int	miller_rabin(__uint64_t number, __uint64_t k)
{
	__uint64_t	base;
	int			first;

	if (number < 3)
		return (0);
	if (number % 2 == 0)
		return (0);
	first = 1;
	while (k > 0)
	{
		base = random_int_64(2, number - 2);
		if (witness(base, number))
			return (0);
		if (first)
		{
			first = 0;
			ft_printf(".");
		}
		k--;
		ft_printf("+");
	}
	ft_printf("\n");
	return (1);
}

int	k_by_accuracy(float accuracy)
{
	int		k;
	float	error_prob;

	k = 1;
	error_prob = 0.25;
	while (error_prob > (1 - accuracy))
	{
		error_prob /= 4;
		k++;
	}
	return (k);
}

int	ft_ssl_is_primary(__uint64_t number, float probability)
{
	int k;

	k = k_by_accuracy(probability);
	return (miller_rabin(number, k));
}
