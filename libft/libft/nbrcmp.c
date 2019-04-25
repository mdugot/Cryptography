/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 12:39:45 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/05 13:29:27 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	min_of(int n, int *tab)
{
	int		result;
	int		tmp;
	int		i;

	i = 0;
	while (i < n)
	{
		tmp = tab[i];
		if (i == 0)
			result = tmp;
		else if (tmp < result)
			result = tmp;
		i++;
	}
	return (result);
}

int	max_of(int n, int *tab)
{
	int		result;
	int		tmp;
	int		i;

	i = 0;
	while (i < n)
	{
		tmp = tab[i];
		if (i == 0)
			result = tmp;
		else if (tmp > result)
			result = tmp;
		i++;
	}
	return (result);
}
