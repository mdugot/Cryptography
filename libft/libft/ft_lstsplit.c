/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:48:56 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 17:45:55 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsplit(char const *s, char c)
{
	char	**tab_temp;
	t_list	*result;
	t_list	*temp;
	int		i;

	tab_temp = ft_strsplit(s, c);
	if (tab_temp == NULL)
		return (NULL);
	i = 0;
	result = NULL;
	while (tab_temp[i] != NULL)
	{
		temp = ft_lstnew(tab_temp[i], ft_strlen(tab_temp[i]) + 1);
		ft_lstadd_end(&result, temp);
		ft_strdel(&(tab_temp[i]));
		i++;
	}
	ft_memdel((void**)&tab_temp);
	return (result);
}
