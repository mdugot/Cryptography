/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   der.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:35:17 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:36:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DER_H
# define DER_H

# include "tools.h"
# include "error.h"
# include "padding.h"
# define DER_INT 11
# define DER_SEQ 2
# define DER_VERSION 3

void	check_is_sequence(size_t (reader)(char*, size_t));
size_t	read_length(size_t (reader)(char*, size_t));
void	read_integer(size_t (reader)(char*, size_t), char *i, size_t len);
char	pass_data(size_t (reader)(char*, size_t));
void	check_is_bits(size_t (reader)(char*, size_t));
void	write_integer(char *buff, __uint64_t i, size_t *l, size_t expectlen);
void	write_sequence(char *buff, char length, size_t *len);
void	write_version(char *buff, size_t *len);

#endif
