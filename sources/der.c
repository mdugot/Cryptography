/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   der.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:28:50 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 16:38:35 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "der.h"

char	next_none_zero(size_t (reader)(char*, size_t))
{
	char	byte;
	size_t	r;

	byte = 0;
	while (byte == 0)
	{
		r = reader(&byte, 1);
		if (r < 1)
			basic_error("wrong der format : end of file");
	}
	return (byte);
}

void	check_is_sequence(size_t (reader)(char*, size_t))
{
	char byte;

	byte = next_none_zero(reader);
	if (byte != 0x30)
		basic_error("wrong der format : sequence not found");
}

void	check_is_bits(size_t (reader)(char*, size_t))
{
	char byte;

	byte = next_none_zero(reader);
	if (byte != 0x03)
		basicError("wrong der format : bits string not found");
}

size_t	read_length(size_t (reader)(char*, size_t))
{
	char	byte;
	char	nbytes;
	size_t	length;

	if (reader(&byte, 1) != 1)
		basic_error("wrong der format : length not found");
	if (!(byte & 0x80))
		return (byte);
	nbytes = byte ^ 0x80;
	if ((size_t)nbytes > sizeof(size_t))
		basic_error("wrong der format : length too big");
	if (reader((char*)&length, nbytes) != (size_t)nbytes)
		basic_error("wrong der format : unable to read length");
	reverse_endian((char*)&length, nbytes);
	return (length);
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

void	read_integer(size_t (reader)(char*, size_t), char *integer, size_t len)
{
	char	byte;
	size_t	r;

	r = reader(&byte, 1);
	if (r != 1 || byte != 0x02)
		basic_error("wrong der format : integer not found");
	r = read_length(reader);
	r = skip_zero(reader, len, r);
	if (reader(integer, r) != r)
		basic_error("wrong der format : unable to read integer");
	reverse_endian(integer, r);
}

char	pass_data(size_t (reader)(char*, size_t))
{
	char	byte;
	char	buff[1001];
	size_t	r;

	r = reader(&byte, 1);
	r = read_Length(reader);
	if (r >= 1000)
		basic_error("wrong der format : too many data to pass");
	if (reader(buff, r) != r)
		basic_error("wrong der format : unable to read integer");
	return (byte);
}

void	append(char *buff, char *content, size_t length, size_t *len)
{
	size_t i;
	size_t from;

	i = 0;
	from = *len;
	while (i < length)
	{
		buff[from + i] = content[i];
		i++;
		*len = *len + 1;
	}
}

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
