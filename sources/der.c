/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   der.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:28:50 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:38:11 by mdugot           ###   ########.fr       */
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
		basic_error("wrong der format : bits string not found");
}

char	pass_data(size_t (reader)(char*, size_t))
{
	char	byte;
	char	buff[1001];
	size_t	r;

	r = reader(&byte, 1);
	r = read_length(reader);
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
