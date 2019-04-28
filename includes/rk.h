/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rk.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:59:10 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 16:52:44 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RK_H
# define RK_H

# include "tools.h"
# include "error.h"
# include "check.h"
# define RK_BUFF_SIZE 256

struct s_command;

typedef struct			s_rk
{
	char				*ftext;
	char				*stext;
	char				*search;
	__uint64_t			hash;
	__uint64_t			whash;
	__uint64_t			len;
	size_t				window_start;
	char				*window_buff;
	size_t				idx;
	int					found;
	size_t				(*reader)(char*, size_t);
}						t_rk;

void					check_rk(t_sslarg *arg, struct s_command *command);
void					execute_rk(struct s_command *command);
void					rabin_karp(t_rk *cmd);
__uint64_t				rk_hash(char *str, size_t length);

#endif
