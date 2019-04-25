/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:13:30 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 13:14:09 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "arg.h"
# include "tools.h"

void wrong_arg(t_sslarg *arg, char *message);
void wrong_command(char *message);
void check_command(t_sslarg *arg);
void wrong_file(char *filename, char *message);
void basic_error(char *message);
void rsa_error(char *message);

#endif
