/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   der2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:34:04 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:38:08 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "der.h"

void	write_sequence(char *buff, char length, size_t *len)
{
	char byte;

	if (length >= 127)
		basic_error("wrong der format : too long sequence to write");
	byte = 0x30;
	append(buff, &byte, 1, len);
	append(buff, &length, 1, len);
}

void	write_integer(char *buff, __uint64_t integer, \
		size_t *len, size_t expected_length)
{
	char	byte;
	size_t	i;

	byte = 0x02;
	append(buff, &byte, 1, len);
	byte = expected_length;
	append(buff, &byte, 1, len);
	i = 8;
	byte = 0;
	while (i < expected_length)
	{
		append(buff, &byte, 1, len);
		i++;
	}
	reverse_endian((char*)&integer, 8);
	i = 0;
	if (expected_length < 8)
		i = 8 - expected_length;
	append(buff, (char*)&integer + i, 8 - i, len);
}

void	write_version(char *buff, size_t *len)
{
	char byte;

	byte = 0x02;
	append(buff, &byte, 1, len);
	byte = 0x01;
	append(buff, &byte, 1, len);
	byte = 0x00;
	append(buff, &byte, 1, len);
}

size_t	skip_zero(size_t (reader)(char*, size_t), size_t expectl, size_t reall)
{
	char	byte;
	size_t	r;

	while (reall > expectl)
	{
		r = reader(&byte, 1);
		if (r != 1 || byte != 0x0)
			basic_error("wrong der format : length too big");
		reall--;
	}
	return (reall);
}
