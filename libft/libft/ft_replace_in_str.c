/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 08:23:12 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/21 14:07:58 by tomo-chan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*do_recursive(char *found, char *to_repl, char *by,
					int recurse)
{
	char		*tmp;

	if (recurse && ft_strcmp(to_repl, by) != 0)
	{
		tmp = ft_replace_in_str(found, to_repl, by, 1);
		if (tmp)
		{
			ft_strdel(&found);
			found = tmp;
		}
	}
	return (found);
}

static char		*cpy_in_found(char *found, char *str, char *by, char *to_repl)
{
	size_t	unch_start;
	int		i;
	int		long_i;

	i = 0;
	long_i = 0;
	unch_start = found - str;
	while (long_i < (int)unch_start)
	{
		found[i] = str[i];
		i++;
		long_i++;
	}
	long_i += ft_strlen(to_repl);
	ft_strcat(found, by);
	ft_strcat(found, &str[long_i]);
	return (found);
}

char			*ft_replace_in_str(char *str, char *to_repl, char *by,
					int recurse)
{
	char	*found;
	char	*tmp;

	tmp = NULL;
	found = ft_strstr(str, to_repl);
	if (found)
	{
		found = ft_strnew(ft_strlen(str) - ft_strlen(to_repl) +
			ft_strlen(by) + 1);
		found = cpy_in_found(found, str, by, to_repl);
		found = do_recursive(found, to_repl, by, recurse);
		return (found);
	}
	return (NULL);
}
