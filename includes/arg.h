/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:00:07 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 13:01:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# include "option.h"

t_sslarg				*new_arg(int argc, char *argv[], t_list *o, char *c);
void					print_arg(t_sslarg *arg);

#endif
