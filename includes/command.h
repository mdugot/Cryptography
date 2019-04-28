/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:02:30 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 13:08:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "arg.h"
# include "error.h"
# include "md5.h"
# include "sha256.h"
# include "des.h"
# include "rsa.h"
# include "luhn.h"

typedef struct			s_command
{
	char				name[100];
	void				*param;
	void				(*checker)(t_sslarg *arg, struct s_command *command);
	void				(*executer)(struct s_command *command);
}						t_command;

t_command				*new_command(char *name, t_list **cmdlist,\
						void (*checker)(t_sslarg *arg, struct s_command *c),\
						void (*executer)(struct s_command *command));
t_command				*find_command(t_list *cmdlist, char *name);
void					execute_command(t_sslarg *arg);
void					init_all_commands();
void					free_cmdlist();

#endif
