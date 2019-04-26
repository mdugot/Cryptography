/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:30:13 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:33:18 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "error.h"

size_t		div_ceil(size_t a, size_t b)
{
	return (a / b) + (a % b > 0 ? 1 : 0);
}

void		random_read(char *bytes, size_t length, char *randdev)
{
	static int	fd = -1;
	size_t		r;

	if (randdev)
	{
		if (fd != -1)
			close(fd);
		fd = open(randdev, O_RDONLY);
		if (fd < 0)
			basic_error("can not open file for generate random number");
	}
	if (bytes == NULL)
		return ;
	if (fd == -1)
		fd = open(RANDOM_DEVICE, O_RDONLY);
	if (fd < 0)
		basic_error("can not open random device for generate random number");
	r = read(fd, bytes, length);
	if (r != length)
		basic_error("error while reading \
				random device for generate random number");
}

__uint64_t	random_int_64(__uint64_t min, __uint64_t max)
{
	__uint64_t result;

	random_read((char*)&result, sizeof(__uint64_t), NULL);
	result = result >> 1;
	return (result % (max - min + 1) + min);
}

__uint64_t	modular_pow(__uint64_t base, __uint64_t e, __uint64_t mod)
{
	__uint64_t result;

	if (mod == 1)
		return (0);
	base = base % mod;
	result = 1;
	while (e > 0)
	{
		if (e % 2 == 1)
			result = (result * base) % mod;
		e = e >> 1;
		base = (base * base) % mod;
	}
	return (result);
}
