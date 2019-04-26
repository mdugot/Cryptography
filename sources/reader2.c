/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:06:16 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:07:13 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

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

size_t	read_from_arg_64(char *buff, size_t length)
{
	char buff_64[1001];

	if (length >= 1001)
		basic_error("can not read more than 1000 bytes from base64 string");
	return (read_base_64(read_from_arg, buff, buff_64, length));
}
