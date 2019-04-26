/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   der3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:34:32 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:37:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "der.h"

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
