/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmaxsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/31 14:21:37 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 13:28:13 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstmaxsize(t_list *lst)
{
	size_t size_next;

	if (lst == NULL)
		return (0);
	size_next = ft_lstmaxsize(lst->next);
	return (lst->content_size > size_next ? lst->content_size : size_next);
}
