/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 10:53:27 by mdugot            #+#    #+#             */
/*   Updated: 2016/02/15 18:14:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelin(t_list **alst, t_list *elem, void (*del)(void*, size_t))
{
	t_list *before;

	if ((alst == NULL || *alst == NULL) || elem == NULL)
		return ;
	if (*alst == elem)
		*alst = elem->next;
	else
	{
		before = ft_lstbefore(*alst, elem);
		if (before != NULL)
			before->next = elem->next;
	}
	if (elem->content != NULL)
		del(elem->content, elem->content_size);
	free(elem);
}

void	ft_lstdelin_memdel(t_list **alst, t_list *elem)
{
	t_list *before;

	if ((alst == NULL || *alst == NULL) || elem == NULL)
		return ;
	if (*alst == elem)
		*alst = elem->next;
	else
	{
		before = ft_lstbefore(*alst, elem);
		if (before != NULL)
			before->next = elem->next;
	}
	if (elem->content != NULL)
		ft_memdel(&(elem->content));
	free(elem);
}
