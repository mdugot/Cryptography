/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbefore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 10:57:23 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 11:15:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstbefore(t_list *lst, t_list *elem)
{
	if (lst == elem)
		return (NULL);
	while (lst->next != elem && lst->next != NULL)
		lst = lst->next;
	if (lst->next == NULL)
		return (NULL);
	else
		return (lst);
}
