/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cur_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:32:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/05/23 15:11:14 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cut_cur_word(char *str, int index)
{
	int		start;
	size_t	len;

	while (index - 1 >= 0 && str[index - 1] != ' ')
		index--;
	start = index;
	len = 0;
	while (str[index] && str[index] != ' ')
	{
		index++;
		len++;
	}
	return (ft_strsub(str, start, len));
}
