/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:26:19 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 14:39:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

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

size_t	read_from_buff(char *buffer, size_t max_size)
{
	char	*arg;
	char	*endarg;
	size_t	size;

	size = 0;
	arg = buff_read_access(NULL, 0);
	endarg = buff_read_access(NULL, 1);
	while (size < max_size && arg < endarg)
	{
		buffer[size] = *arg;
		size++;
		arg++;
	}
	buff_read_access(arg, endarg - arg);
	return (size);
}

size_t	read_from_fd(char *buffer, size_t max_size)
{
	int		size;
	int		fd;
	size_t	length;

	fd = fd_read_access(NULL);
	ft_bzero(buffer, max_size);
	size = 1;
	length = 0;
	while (length < max_size && size > 0)
	{
		size = (int)read(fd, &buffer[length], (max_size - length));
		length += size;
	}
	if (size == -1)
		basic_error("error while reading from file descriptor");
	return (length);
}

size_t	read_from_arg(char *buffer, size_t max_size)
{
	char	*arg;
	size_t	size;

	size = 0;
	arg = arg_read_access(NULL);
	while (size < max_size && arg[size])
	{
		buffer[size] = arg[size];
		size++;
	}
	arg_read_access(&arg[size]);
	buffer[size] = 0;
	return (size);
}

size_t	read_no_white_space(size_t (reader)(char*, size_t), \
		char *buffer, size_t max_size)
{
	char	whites[] = " \t\n\r";
	char	*found;
	size_t	length;
	size_t	size;
	size_t	skip;

	size = reader(buffer, max_size);
	length = size;
	while (ft_first_of(buffer, whites, length))
	{
		skip = 0;
		while ((found = ft_first_of(buffer, whites, length - skip)) != NULL)
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

size_t	read_from_arg_64(char *buff, size_t length)
{
	char buff_64[1001];

	if (length >= 1001)
		basic_error("can not read more than 1000 bytes from base64 string");
	return (read_base_64(read_from_arg, buff, buff_64, length));
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
