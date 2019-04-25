/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:11:55 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 11:41:36 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*temp;

	if (alst == NULL || del == NULL)
		return ;
	temp = *alst;
	if (temp->content != NULL)
		del(temp->content, temp->content_size);
	free(temp);
	*alst = NULL;
}
