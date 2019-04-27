/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:43:36 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 17:04:30 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEXA_H
# define HEXA_H

# include "padding.h"

unsigned long int	key_from_string(char *str);
char				*colons_hexa(char *bytes, size_t len);

#endif
