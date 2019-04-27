/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:17:00 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 14:36:14 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

# include "tools.h"

typedef struct			s_pair
{
	char				*key;
	char				*value;
}						t_pair;

typedef struct			s_sslarg
{
	int					argc;
	char				**argv;
	t_list				*options;
	char				*command;
}						t_sslarg;

t_pair					*new_pair(char *key, char *value);
t_sslarg				*parse_options(int argc, char *argv[]);
void					delete_pair(void *ad, size_t size);
t_pair					*new_pair(char *key, char *value);
void					print_option(t_list *elem);

#endif
