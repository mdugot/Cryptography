/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:48:12 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:48:56 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "arg.h"

t_pair		*new_pair(char *key, char *value)
{
	t_pair *pair;

	pair = ft_memalloc(sizeof(t_pair));
	if (key == NULL)
		pair->key = NULL;
	else
		pair->key = ft_strdup(key);
	if (value == NULL)
		pair->value = NULL;
	else
		pair->value = ft_strdup(value);
	return (pair);
}

void		delete_pair(t_pair *pair, size_t size)
{
	(void)size;
	if (pair->key != NULL)
		free(pair->key);
	if (pair->value != NULL)
		free(pair->value);
	free(pair);
}

void		print_option(t_list *elem)
{
	t_pair *pair;

	pair = elem->content;
	if (pair->value == NULL)
		ft_printf_fd(2, "%s\n", pair->key);
	else
		ft_printf_fd(2, "%s = %s\n", pair->key, pair->value);
}
