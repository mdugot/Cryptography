/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:12:40 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/27 16:28:22 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;

	if (lst == NULL)
		return (NULL);
	result = ft_lstnew(lst->content, lst->content_size);
	if (f != NULL)
		result = f(result);
	if (lst->next != NULL)
		result->next = ft_lstmap(lst->next, f);
	return (result);
}
