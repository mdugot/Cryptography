/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:59:18 by mdugot            #+#    #+#             */
/*   Updated: 2015/12/31 18:47:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_str(char const *s, char c)
{
	int result;
	int first;
	int i;

	i = 0;
	first = 0;
	result = 0;
	while (s[i] != 0)
	{
		if (first == 0 && s[i] != c)
		{
			result++;
			first = 1;
		}
		else if (first == 1 && s[i] == c)
			first = 0;
		i++;
	}
	return (result);
}

static int	next_size(char const *s, char c, int i)
{
	int result;

	result = 0;
	while (s[i] == c)
		i++;
	while (s[i + result] != c && s[i + result] != '\0')
		result++;
	return (result);
}

static char	*next_word(char const *s, char c, int *i)
{
	char	*result;
	int		size;
	int		j;

	size = next_size(s, c, *i);
	result = ft_strnew(size + 1);
	if (result == NULL)
		return (NULL);
	while (s[*i] == c)
		*i += 1;
	j = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		result[j] = s[*i];
		j++;
		*i += 1;
	}
	return (result);
}

size_t		ft_strsplit_size(char **split)
{
	size_t	size;

	size = 0;
	while (split[size] != NULL)
		size++;
	return (size);
}

char		**ft_strsplit(char const *s, char c)
{
	int		size;
	int		n;
	int		i;
	char	**result;

	if (s == NULL)
		size = 0;
	else
		size = number_str(s, c);
	result = ft_memalloc(sizeof(char*) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	i = 0;
	n = 0;
	while (n < size)
	{
		result[n] = next_word(s, c, &i);
		if (result[n] == NULL)
			return (NULL);
		n++;
	}
	return (result);
}
