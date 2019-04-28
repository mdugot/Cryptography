/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luhn.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 10:51:17 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 11:10:04 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUHN_H
# define LUHN_H

# include "tools.h"
# include "error.h"

struct s_command;

typedef struct			s_luhn
{
	__uint64_t			number;
	__uint64_t			modulus;
}						t_luhn;

void					check_luhn(t_sslarg *arg, struct s_command *command);
void					execute_luhn(struct s_command *command);

#endif
