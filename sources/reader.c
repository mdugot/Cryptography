/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:26:19 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:07:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

char	g_whites[] = " \t\n\r";

int		fd_read_access(char *filename)
{
	static int fd = 0;

	if (filename != NULL)
	{
		if (fd != 0)
			close(fd);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			wrong_file(filename, "can not open file");
	}
	return (fd);
}

char	*arg_read_access(char *a)
{
	static char *arg = NULL;

	if (a != NULL)
		arg = a;
	return (arg);
}

char	*buff_read_access(char *a, size_t l)
{
	static char		*arg = NULL;
	static size_t	length = 0;

	if (a != NULL)
	{
		arg = a;
		length = l;
		return (0);
	}
	if (!l)
		return (arg);
	return (arg + length);
}

size_t	read_no_white_space(size_t (reader)(char*, size_t), \
		char *buffer, size_t max_size)
{
	char	*found;
	size_t	length;
	size_t	size;
	size_t	skip;

	size = reader(buffer, max_size);
	length = size;
	while (ft_first_of(buffer, g_whites, length))
	{
		skip = 0;
		while ((found = ft_first_of(buffer, g_whites, length - skip)) != NULL)
		{
			if (found < (buffer + length - 1))
				ft_memmove(found, found + 1, (buffer + length) - (found + 1));
			skip++;
		}
		length -= skip;
		if (size == max_size)
		{
			max_size = max_size - size + skip;
			size = reader(buffer + length, max_size);
			length += size;
		}
	}
	return (length);
}

size_t	read_base_64(size_t (reader)(char*, size_t), \
		char *buffer, char *buffer_64, size_t max_size)
{
	static char		memory[3] = {0};
	static size_t	extra = 0;
	size_t			length;
	size_t			rlen;
	char			*dbg;

	length = 0;
	dbg = buffer;
	while (extra > 0 && max_size > 0)
	{
		*buffer = memory[0];
		buffer++;
		ft_memmove(memory, memory + 1, 2);
		extra--;
		length++;
		max_size--;
	}
	if (max_size == 0)
		return (length);
	rlen = read_no_white_space(reader, buffer_64, div_ceil(max_size, 3) * 4);
	rlen = base_64_decode(buffer_64, rlen, buffer_64);
	extra = rlen > max_size ? rlen - max_size : 0;
	ft_memcpy(buffer, buffer_64, rlen - extra);
	ft_memcpy(memory, buffer_64 + max_size, extra);
	return (length + rlen - extra);
}
