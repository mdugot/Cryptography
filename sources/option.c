/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:08:09 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/28 15:43:47 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "arg.h"

const char	*g_container[] = {
	"#rabin-karp",
	"file",
	"string",
	"search",
	"#luhn",
	"m",
	"#rsa#rsautl",
	"inform",
	"outform",
	"in",
	"out",
	"passin",
	"passout",
	"inkey",
	"#des#des-ecb#des-cbc",
	"p",
	"#md5#sha256#genrsa#base64",
	"s",
	"i",
	"o",
	"k",
	"v",
	"rand",
	NULL
};

int			is_container(char *name, char *str)
{
	int		i;
	int		skip;
	char	*ad;

	i = 0;
	skip = 1;
	while (g_container[i] != NULL)
	{
		ad = ft_strstr(g_container[i], name);
		if (ad && ad > g_container[i] && ad[-1] == '#')
			skip = 0;
		if (!skip && ft_strcmp(str, g_container[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void		next_arg(t_sslarg *arg)
{
	arg->argc = arg->argc - 1;
	arg->argv = &arg->argv[1];
}

int			expect_content(char *name, t_pair *last)
{
	if (last == NULL || last->key == NULL || last->value != NULL)
		return (0);
	return (is_container(name, last->key));
}

t_pair		*parse_one_arg(t_sslarg *arg, t_pair *last, int *end)
{
	if (arg->command != NULL && expect_content(arg->command, last))
		last->value = ft_strdup(arg->argv[0]);
	else if (ft_strcmp("--", arg->argv[0]) == 0)
	{
		*end = 1;
		next_arg(arg);
	}
	else if (*end == 0 && arg->argv[0][0] == '-')
	{
		last = new_pair(arg->argv[0] + 1, NULL);
		ft_lstadd_end(&arg->options, ft_lstnew_noalloc(last, sizeof(t_pair)));
	}
	else
	{
		if (arg->command == NULL)
			arg->command = arg->argv[0];
		else
			*end = 1;
	}
	return (last);
}

t_sslarg	*parse_options(int argc, char *argv[])
{
	t_sslarg	*arg;
	t_pair		*last;
	int			end;

	end = 0;
	arg = new_arg(argc, argv, NULL, NULL);
	last = NULL;
	while (arg->argc > 1 && !(arg->command && end))
	{
		next_arg(arg);
		last = parse_one_arg(arg, last, &end);
	}
	if (end == 0)
		next_arg(arg);
	return (arg);
}
