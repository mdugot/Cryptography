/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:18:54 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 13:19:42 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSWORD_H
# define PASSWORD_H

# define PASSWORD_LEN 128
# include "tools.h"
# include "error.h"
# include "hexa.h"
# include "md5.h"

struct s_des;

char	*ask_password();
void	des_password(struct s_des *des);

#endif
