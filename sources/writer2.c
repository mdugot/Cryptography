/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:26:04 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:26:26 by mdugot           ###   ########.fr       */
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
