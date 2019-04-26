/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:14:36 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:58:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "padding.h"
# include "digest.h"

struct s_command;
void			execute_md5(struct s_command *command);
unsigned int	*hash_md5(char *str);
void			md5_update(unsigned int *state, unsigned int *word);
unsigned int	*md5_init_state(void);

#endif
