/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:57:38 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 17:58:17 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_before(t_list **alst, t_list *old, t_list *new)
{
	t_list *temp;

	if ((alst == NULL || *alst == NULL) || new == NULL || old == NULL)
		return ;
	if (*alst == old)
	{
		ft_lstadd(alst, new);
		return ;
	}
	temp = ft_lstbefore(*alst, old);
	if (temp == NULL)
		return ;
	new->next = old;
	temp->next = new;
}
