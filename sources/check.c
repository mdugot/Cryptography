/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:15:29 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 16:22:09 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

int		has_option(t_sslarg *arg, char *to_check)
{
	t_list *tmp;
	t_pair *pair;

	tmp = arg->options;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, to_check) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	allow_options(t_sslarg *arg, char **options)
{
	t_list	*tmp;
	t_pair	*pair;
	int		ok;
	int		i;

	tmp = arg->options;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		ok = 0;
		i = 0;
		while (options[i])
		{
			if (ft_strcmp(pair->key, options[i]) == 0)
				ok = 1;
			i++;
		}
		if (!ok)
			wrong_arg(arg, ft_strf("unknown option '%s'", pair->key));
		tmp = tmp->next;
	}
}

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

int		count_options(t_sslarg *arg, char *to_check)
{
	t_list	*tmp;
	t_pair	*pair;
	int		i;

	tmp = arg->options;
	i = 0;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, toCheck) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
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
		contents[i] = find_content(arg, toCheck, i);
		i++;
	}
	contents[i] = NULL;
	return (contents);
}
