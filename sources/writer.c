/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:33:27 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:37:45 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer.h"

char			*buff_write_access(char *a, size_t l)
{
	static char		*arg = NULL;
	static size_t	limit = 0;

	if (a != NULL)
	{
		arg = a;
		limit = l;
		return (0);
	}
	if (!l)
		return (arg);
	return (arg + limit);
}

void			write_to_buff(char *buffer, size_t length)
{
	char	*buff;
	char	*endbuff;

	buff = buff_write_access(NULL, 0);
	endbuff = buff_write_access(NULL, 1);
	if (length >= (size_t)(endbuff - buff))
		basic_error("full buffer error");
	ft_memcpy(buff, buffer, length);
	buff_write_access(buff + length, endbuff - buff - length);
}

int				fd_write_access(char *filename)
{
	static int fd = 1;

	if (filename != NULL)
	{
		if (fd != 1)
			close(fd);
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			wrong_file(filename, "can not open file");
	}
	return (fd);
}

void			write_to_fd(char *buffer, size_t length)
{
	int		fd;
	int		result;

	fd = fd_write_access(NULL);
	result = (int)write(fd, buffer, length);
	if (result == -1)
		basic_error("error while writing to file descriptor");
}

void			write_to_fd_64(char *buffer, size_t length)
{
	char str_64[4004] = {0};

	if (length >= 3000)
		basic_error("can not write more than 3000 bytes in base64");
	base_64_encode(buffer, length, str_64);
	write_to_fd_64_line(str_64, ft_strlen(str_64));
}

void			write_to_fd_64_line(char *buffer, size_t length)
{
	static int counter = 0;

	while (length > 0)
	{
		if (counter + length <= 64)
		{
			counter += length;
			write_to_fd(buffer, length);
			length = 0;
		}
		else
		{
			write_to_fd(buffer, 64 - counter);
			buffer += 64 - counter;
			length -= 64 - counter;
			counter = 0;
			write_to_fd("\n", 1);
		}
	}
}
