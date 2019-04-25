/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:01:38 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 13:02:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIT_H
# define BIT_H

# include "tools.h"

char bit_mask(int idx);
void set_bit(char *bytes, int idx, char bit);
char get_bit(char *bytes, int idx);

#endif
