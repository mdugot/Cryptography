/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:05:38 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 15:49:44 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *result;

	result = (t_list*)ft_memalloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
		return (result);
	}
	result->content_size = content_size;
	result->content = ft_memalloc(content_size);
	if (result->content == NULL)
	{
		result->content_size = 0;
		return (NULL);
	}
	else
		ft_memcpy(result->content, content, content_size);
	return (result);
}

t_list	*ft_lstnew_noalloc(void *content, size_t content_size)
{
	t_list *result;

	result = (t_list*)ft_memalloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
		return (result);
	}
	result->content_size = content_size;
	result->content = content;
	if (result->content == NULL)
	{
		result->content_size = 0;
		return (NULL);
	}
	return (result);
}
