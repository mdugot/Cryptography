/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:29:52 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 16:32:20 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "digest.h"
#include "command.h"

unsigned int	*hash(size_t (*reader)(char*, size_t), \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), int print)
{
	char				buff[65];
	unsigned int		*state;
	unsigned long int	size;
	size_t				length;

	state = init_state();
	size = 0;
	length = reader(buff, 64);
	buff[length] = 0;
	if (print)
		ft_putstr(buff);
	digest(buff, state, &size, length);
	while (length >= 64)
	{
		length = reader(buff, 64);
		buff[length] = 0;
		if (print)
			ft_putstr(buff);
		digest(buff, state, &size, length);
	}
	return (state);
}

void			rprint_hash(char *hash, char *string, char *file, char *type)
{
	(void)type;
	if (string)
		ft_printf("%s \"%s\"\n", hash, string);
	else if (file)
		ft_printf("%s %s\n", hash, file);
	else
		ft_printf("%s\n", hash);
}

void			print_hash(char *hash, char *string, char *file, char *type)
{
	if (string)
		ft_printf("%s (\"%s\") = %s\n", type, string, hash);
	else if (file)
		ft_printf("%s (%s) = %s\n", type, file, hash);
	else
		ft_printf("%s\n", hash);
}

void			check_digest(t_sslarg *arg, struct s_command *command)
{
	t_digest *digest;

	digest = ft_memalloc(sizeof(t_digest));
	allow_options(arg, (char*[]){"c", "b", "p", "q", "r", "s", NULL});
	digest->string = get_list_contents(arg, "s");
	digest->reverse = has_option(arg, "r");
	digest->quiet = has_option(arg, "q");
	digest->colon = has_option(arg, "c");
	digest->binary = has_option(arg, "b");
	digest->print_stdin = has_option(arg, "p");
	digest->files = arg->argv;
	digest->nfiles = arg->argc;
	command->param = digest;
}

void			free_digest(t_digest *digest)
{
	if (digest->string)
		ft_memdel((void**)&(digest->string));
	ft_memdel((void**)&digest);
}
