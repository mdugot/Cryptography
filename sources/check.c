/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:15:29 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:23:14 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

char	*find_content(t_sslarg *arg, char *to_check, int idx)
{
	t_list	*tmp;
	t_pair	*pair;
	int		i;

	tmp = arg->options;
	i = 0;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, to_check) == 0)
		{
			if (idx == i)
			{
				if (pair->value == NULL)
					wrong_arg(arg, \
						ft_strf("must have -%s with value", to_check));
				return (pair->value);
			}
			else
				i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_content(t_sslarg *arg, char *to_check)
{
	char *content;

	if (has_option(arg, to_check) == 0)
		return (NULL);
	content = find_content(arg, to_check, 0);
	return (content);
}

char	**get_list_contents(t_sslarg *arg, char *to_check)
{
	char	**contents;
	int		count;
	int		i;

	count = count_options(arg, to_check);
	if (count <= 0)
		return (NULL);
	contents = ft_memalloc((count + 1) * sizeof(char*));
	i = 0;
	while (i < count)
	{
		contents[i] = find_content(arg, to_check, i);
		i++;
	}
	contents[i] = NULL;
	return (contents);
}
