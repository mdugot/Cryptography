/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:31:20 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:32:12 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define RANDOM_DEVICE "/dev/urandom"
# include <unistd.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "colors.h"
# include "get_next_line.h"
# include "libft.h"

size_t		div_ceil(size_t a, size_t b);
void		random_read(char *bytes, size_t length, char *randdev);
__uint64_t	random_int_64(__uint64_t min, __uint64_t max);
__uint64_t	modular_pow(__uint64_t base, __uint64_t e, __uint64_t mod);

#endif
