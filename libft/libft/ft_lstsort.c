/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:23:19 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/27 13:52:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstsort_step(t_list **begin, t_list *before, t_list *elem,\
				int (*cmp)(void *c1, void *c2))
{
	t_list *temp;

	if (begin == NULL || *begin == NULL || elem == NULL || elem->next == NULL)
		return ;
	temp = elem;
	if (cmp(elem->content, elem->next->content) > 0)
	{
		temp = elem->next;
		elem->next = temp->next;
		temp->next = elem;
		if (before != NULL)
		{
			before->next = temp;
			ft_lstsort_step(begin, ft_lstbefore(*begin, before), before, cmp);
		}
		else
			*begin = temp;
	}
	ft_lstsort_step(begin, elem, elem->next, cmp);
}

void		ft_lstsort(t_list **alst, int (*cmp)(void *c1, void *c2))
{
	ft_lstsort_step(alst, NULL, *alst, cmp);
}
