/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:50:44 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:52:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H

# include "error.h"
# include "tools.h"
# include "base64.h"

int				fd_write_access(char *filename);
char			*buff_write_access(char *a, size_t l);
void			write_to_fd(char *buffer, size_t length);
void			write_to_fd_64(char *buffer, size_t length);
void			write_to_buff(char *buffer, size_t length);
void			write_to_fd_64_line(char *buffer, size_t length);

#endif
