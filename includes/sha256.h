/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:50:15 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 18:41:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "check.h"
# include "padding.h"
# include "digest.h"

struct s_command;

void	execute_sha_256(struct s_command *command);
void	update_sha_1(unsigned int *word, \
						unsigned int *w, unsigned int *s);
void	update_sha_2(unsigned int *tmp, \
						unsigned int *w, unsigned int *s);

#endif
