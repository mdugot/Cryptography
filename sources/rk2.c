/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rk2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:44:35 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 16:49:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rk.h"
#include "command.h"

__uint64_t	rk_pow(__uint64_t n, __uint64_t exp)
{
	__uint64_t	i;
	__uint64_t	r;
	__uint64_t	base;

	i = 0;
	r = 1;
	base = 256;
	while (i < exp)
	{
		r *= base;
		i++;
	}
	return (n * r);
}

void		rk_roll(t_rk *cmd, char *buff, size_t i)
{
	if (cmd->idx < cmd->len)
	{
		if (cmd->idx > 0)
			cmd->hash *= 256;
		cmd->hash += (__uint64_t)buff[i];
		cmd->window_buff[cmd->idx] = buff[i];
	}
	else
	{
		cmd->window_start += 1;
		cmd->hash -= rk_pow(cmd->window_buff[0], cmd->len - 1);
		cmd->hash *= 256;
		cmd->hash += (__uint64_t)buff[i];
		ft_memmove(cmd->window_buff, cmd->window_buff + 1, cmd->len - 1);
		cmd->window_buff[cmd->len - 1] = buff[i];
	}
}

void		rabin_karp(t_rk *cmd)
{
	char	buff[RK_BUFF_SIZE + 1];
	size_t	rsize;
	size_t	i;

	rsize = 1;
	while (rsize > 0)
	{
		rsize = cmd->reader(buff, RK_BUFF_SIZE);
		i = 0;
		while (i < rsize)
		{
			rk_roll(cmd, buff, i);
			if (cmd->hash == cmd->whash
				&& !ft_strncmp(cmd->search, cmd->window_buff, cmd->len))
			{
				cmd->found = 1;
				return ;
			}
			i++;
			cmd->idx += 1;
		}
	}
}

__uint64_t	rk_hash(char *str, size_t length)
{
	size_t		i;
	__uint64_t	hash;

	i = 0;
	hash = 0;
	while (i < length)
	{
		if (i > 0)
			hash *= 256;
		hash += (__uint64_t)str[i];
		i++;
	}
	return (hash);
}
