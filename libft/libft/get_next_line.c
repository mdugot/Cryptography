/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:51:40 by mdugot            #+#    #+#             */
/*   Updated: 2015/12/31 17:51:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		initialize(t_buff liste[MAX_FILES])
{
	int i;

	i = 0;
	while (i < MAX_FILES)
	{
		FD = -1;
		i++;
	}
}

static void		update_buff(t_buff *buff)
{
	char	*cr;

	cr = ft_memchr((const void*)buff->buff, '\n', buff->size);
	if (cr == NULL)
		return ;
	while (buff->buff[0] != '\n')
	{
		ft_memmove(buff->buff, &(buff->buff[1]), BUFF_SIZE - 1);
		buff->buff[BUFF_SIZE - 1] = '\0';
		buff->size--;
	}
	ft_memmove(buff->buff, &(buff->buff[1]), BUFF_SIZE - 1);
	buff->buff[BUFF_SIZE - 1] = '\0';
	buff->size--;
	if (buff->size == 0)
		buff->size = -2;
}

static int		find_buff(t_buff liste[MAX_FILES], int fd)
{
	int i;

	i = 0;
	if (FD == -2)
		initialize(liste);
	while (i < MAX_FILES)
	{
		if (FD == fd)
			return (i);
		i++;
	}
	i = 0;
	while (i < MAX_FILES)
	{
		if (FD == -1)
			break ;
		i++;
	}
	if (i == MAX_FILES)
		return (-1);
	FD = fd;
	SIZE = -2;
	return (i);
}

static void		get_next(char buff[BUFF_SIZE], char **line, int size)
{
	char	*new;
	int		l;

	l = 0;
	while (buff[l] != '\n' && l < size)
		l++;
	new = ft_strnew((size_t)l + ft_strlen(*line) + 1);
	if (*line)
		ft_strcpy(new, *line);
	ft_strncat(new, buff, (size_t)l);
	if (*line)
		ft_strdel(line);
	*line = new;
}

int				get_next_line(int const fd, char **line)
{
	static t_buff	liste[MAX_FILES] = {{-2, "", -1}};
	int				i;

	if (OVER_WRITE && line && *line)
		ft_strdel(line);
	if (line == NULL || fd < 0 || (i = find_buff(liste, fd)) == -1)
		return (-1);
	*line = ft_strdup("");
	if (SIZE == -2)
		SIZE = read(fd, (void*)BUFF, BUFF_SIZE);
	if (SIZE > 0)
		get_next(BUFF, line, SIZE);
	while (SIZE > 0 && !ft_memchr((const void*)BUFF, '\n', SIZE))
	{
		SIZE = read(fd, (void*)BUFF, BUFF_SIZE);
		get_next(BUFF, line, SIZE);
	}
	if (SIZE <= 0)
	{
		FD = -1;
		return (SIZE);
	}
	update_buff(&liste[i]);
	return (1);
}
