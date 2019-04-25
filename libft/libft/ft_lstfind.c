/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 16:39:59 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 17:59:22 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *content, int (*cmp)(void *c1, void *c2))
{
	if (lst == NULL || cmp == NULL)
		return (NULL);
	if (cmp(content, lst->content))
		return (lst);
	return (ft_lstfind(lst->next, content, cmp));
}
