/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:22:09 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:23:15 by mdugot           ###   ########.fr       */
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
		if (ft_strcmp(pair->key, to_check) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
