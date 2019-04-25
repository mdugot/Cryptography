/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:34:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/03/31 17:15:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	if (del == NULL)
		return ;
	if (alst == NULL || *alst == NULL)
		return ;
	if ((*alst)->next != NULL)
		ft_lstdel(&((*alst)->next), del);
	ft_lstdelone(alst, del);
}

void	ft_lstfree(t_list **alst)
{
	if (alst == NULL || *alst == NULL)
		return ;
	if ((*alst)->next != NULL)
		ft_lstfree(&((*alst)->next));
	if ((*alst)->content != NULL)
		ft_memdel(&(*alst)->content);
}
