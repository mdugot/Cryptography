/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:04:41 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 19:05:19 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

__int64_t	gcd_extended(__uint64_t a, __uint64_t b, __int64_t *x, __int64_t *y)
{
	__int64_t x1;
	__int64_t y1;
	__int64_t gcd;

	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return (b);
	}
	gcd = gcd_extended(b % a, a, &x1, &y1);
	*x = ((__uint64_t)y1 - (b / a) * (__uint64_t)x1);
	*y = x1;
	return (gcd);
}

int			is_coprime(__uint64_t n1, __uint64_t n2)
{
	__uint64_t i;

	i = 2;
	while (i <= n2)
	{
		if (i % n1 == 0 && i % n2 == 0)
			return (0);
		i++;
	}
	return (1);
}

void		random_prime_pair(t_rsakey *key, \
			int (*is_primary)(__uint64_t, float), float probability)
{
	key->prime1 = 0;
	while (key->prime1 == 0 || !is_primary(key->prime1, probability))
		key->prime1 = random_int_64(RANDMIN, RANDMAX);
	key->prime2 = 0;
	while (key->prime2 == 0
		|| !is_primary(key->prime2, probability)
		|| !is_coprime((key->prime1 - 1) * (key->prime2 - 1), \
						key->public_exponent))
		key->prime2 = random_int_64(RANDMIN, RANDMAX);
}

t_rsakey	*create_rsa_key(int (*is_primary)(__uint64_t, float), \
			float probability)
{
	t_rsakey	*key;
	__uint64_t	phi;
	__int64_t	x;
	__int64_t	y;
	__int64_t	r;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	key->public_exponent = 65537;
	random_prime_pair(key, is_primary, probability);
	ft_printf("e is 65537 (0x10001)\n");
	phi = (key->prime1 - 1) * (key->prime2 - 1);
	r = gcd_extended(key->public_exponent, phi, &x, &y);
	key->private_exponent = (__uint64_t)(x < 0 ? (phi + x) : x);
	key->modulus = key->prime1 * key->prime2;
	key->exponent_1 = key->private_exponent % (key->prime1 - 1);
	key->exponent_2 = key->private_exponent % (key->prime2 - 1);
	key->coefficient = modular_pow(key->prime2, key->prime1 - 2, key->prime1);
	return (key);
}

void		print_rsa_key(t_rsakey *key)
{
	ft_printf("Private-Key: (64 bit)\n");
	ft_printf("modulus: %lld (%#llx)\n", key->modulus, key->modulus);
	ft_printf("public_exponent: %lld (%#llx)\n", \
			key->public_exponent, key->public_exponent);
	ft_printf("private_exponent: %lld (%#llx)\n", \
			key->private_exponent, key->private_exponent);
	ft_printf("prime1: %lld (%#llx)\n", key->prime1, key->prime1);
	ft_printf("prime2: %lld (%#llx)\n", key->prime2, key->prime2);
	ft_printf("exponent1: %lld (%#llx)\n", key->exponent_1, key->exponent_1);
	ft_printf("exponent2: %lld (%#llx)\n", key->exponent_2, key->exponent_2);
	ft_printf("coefficient: %lld (%#llx)\n", \
			key->coefficient, key->coefficient);
}
