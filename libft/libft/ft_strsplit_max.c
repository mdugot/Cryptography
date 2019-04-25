/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 16:26:38 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/13 18:14:03 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_str(char const *s, char c, int max)
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
	if (result < max)
		return (result);
	else
		return (max);
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

static char	*last_word(char const *s, char c, int *i)
{
	char	*result;
	int		j;

	while (s[*i] == c)
		*i += 1;
	result = ft_strdup(&s[*i]);
	j = ft_strlen(result) - 1;
	while (result[j] == c && j >= 0)
	{
		result[j] = '\0';
		j--;
	}
	return (result);
}

char		**ft_strsplit_max(char const *s, char c, int max)
{
	int		size;
	int		n;
	int		i;
	char	**result;

	if (s == NULL)
		size = 0;
	else
		size = number_str(s, c, max);
	result = ft_memalloc(sizeof(char*) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	i = 0;
	n = -1;
	while (++n < size)
	{
		if (n == max - 1)
			result[n] = last_word(s, c, &i);
		else
			result[n] = next_word(s, c, &i);
		if (result[n] == NULL)
			return (NULL);
	}
	return (result);
}
