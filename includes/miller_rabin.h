/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miller_rabin.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:44:46 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:45:07 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MILLER_RABIN_H
# define MILLER_RABIN_H

# include "tools.h"

int miller_rabin(__uint64_t number, __uint64_t k);
int ft_ssl_is_primary(__uint64_t number, float probability);

#endif
