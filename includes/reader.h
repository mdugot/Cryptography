/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:46:38 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:50:08 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "error.h"
# include "tools.h"
# include "base64.h"

int				fd_read_access(char *filename);
char			*arg_read_access(char *a);
size_t			read_from_fd(char *buffer, size_t max_size);
size_t			read_from_arg(char *buffer, size_t max_size);
size_t			read_no_white_space(size_t (reader)(char*, size_t), \
		char *buffer, size_t max_size);
size_t			read_base_64(size_t (reader)(char*, size_t), \
		char *buffer, char *buffer64, size_t max_size);
size_t			read_from_arg_64(char *buff, size_t length);
size_t			read_from_buff(char *buffer, size_t max_size);
char			*buff_read_access(char *a, size_t l);

#endif
