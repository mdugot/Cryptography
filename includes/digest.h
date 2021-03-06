/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:37:22 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/27 16:26:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

# include "tools.h"
# include "check.h"

struct s_command;

typedef struct			s_digest
{
	int					reverse;
	int					quiet;
	int					colon;
	int					binary;
	int					print_stdin;
	int					nfiles;
	char				**files;
	char				**string;
}						t_digest;

unsigned int			*hash(size_t (*reader)(char*, size_t), \
		void (*digest)(char*, unsigned int*, unsigned long int*, size_t), \
		unsigned int *(*init_state)(), int print);
void					print_hash(char *h, char *str, char *f, char *t);
void					rprint_hash(char *h, char *str, char *f, char *t);
void					check_digest(t_sslarg *arg, struct s_command *command);
void					free_digest(t_digest *digest);
void					execute_digest(struct s_command *command, \
		void (*digest)(char*, unsigned int*, \
		unsigned long int*, size_t), \
		unsigned int *(*init_state)(), \
		void (*print_result)(unsigned int *, char*, char*, t_digest *));

#endif
