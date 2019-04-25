/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:45:17 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:46:28 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PADDING_H
# define PADDING_H

# include "tools.h"

char			*pad(char *str, long unsigned int size, int *nb, size_t len);
void			pkcs(char *bytes, size_t block_size, size_t length);
unsigned int	leftrotate(unsigned int value, unsigned int shift);
unsigned int	rightrotate(unsigned int value, unsigned int shift);
void			reverse_endian(char *bytes, int length);

#endif
