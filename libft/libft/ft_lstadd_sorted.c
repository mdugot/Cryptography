/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:12:13 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/27 14:45:47 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_sorted(t_list **alst, t_list *elem,\
		int (*cmp)(void *c1, void *c2))
{
	if (alst == NULL || elem == NULL || cmp == NULL)
		return ;
	if (*alst == NULL)
	{
		ft_lstadd(alst, elem);
		return ;
	}
	if (cmp(elem->content, (*alst)->content) <= 0)
		ft_lstadd_before(alst, *alst, elem);
	else if ((*alst)->next == NULL)
		(*alst)->next = elem;
	else
		ft_lstadd_sorted(&((*alst)->next), elem, cmp);
}

void	ft_lstadd_sorted_o(t_list **alst, t_list *elem, void *option,\
		int (*cmp)(void *c1, void *c2, void *opt))
{
	if (alst == NULL || elem == NULL || cmp == NULL)
		return ;
	if (*alst == NULL)
	{
		ft_lstadd(alst, elem);
		return ;
	}
	if (cmp(elem->content, (*alst)->content, option) <= 0)
		ft_lstadd_before(alst, *alst, elem);
	else if ((*alst)->next == NULL)
		(*alst)->next = elem;
	else
		ft_lstadd_sorted_o(&((*alst)->next), elem, option, cmp);
}
