/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 14:11:12 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/18 14:00:03 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_special(char c)
{
	if (c == '\0')
		return (0);
	if (ft_strchr("%#", c))
		return (1);
	return (0);
}

int		is_specifier(char c)
{
	if (c == '\0')
		return (0);
	if (ft_strchr("sSpdDioOuUxXcCfFbB?", c))
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '\0')
		return (0);
	if (ft_strchr("#0-+ hljz", c))
		return (1);
	return (0);
}

int		is_expr(char c)
{
	if (c == '\0')
		return (0);
	if (ft_isdigit(c))
		return (1);
	if (c == '.')
		return (1);
	if (is_specifier(c))
		return (1);
	if (is_flag(c))
		return (1);
	if (c == '*')
		return (1);
	return (0);
}

char	*find_next_special(char *str)
{
	while (!is_special(*str))
	{
		if (*str == '\0')
			return (str);
		str++;
	}
	return (str);
}
