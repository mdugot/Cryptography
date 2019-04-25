/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:33:52 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:34:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H

# include "error.h"
# include "tools.h"
# include "reader.h"

int		has_option(t_sslarg *arg, char *to_check);
char	*get_content(t_sslarg *arg, char *to_check);
char	**get_list_contents(t_sslarg *arg, char *to_check);
void	allow_options(t_sslarg *arg, char **options);

#endif
