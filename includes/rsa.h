/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:21:18 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 19:09:18 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include "tools.h"
# include "error.h"
# include "reader.h"
# include "writer.h"
# include "check.h"
# include "der.h"
# include "des.h"
# include "miller_rabin.h"
# define RANDMAX 0xFFFF
# define RANDMIN 0x1000
# define KEYMAXBODY 1000

struct s_command;

typedef struct			s_rsakey
{
	__uint64_t			prime1;
	__uint64_t			prime2;
	__uint64_t			modulus;
	__uint64_t			public_exponent;
	__uint64_t			private_exponent;
	__uint64_t			exponent_1;
	__uint64_t			exponent_2;
	__uint64_t			coefficient;
	int					public_key;
}						t_rsakey;

typedef struct			s_rsautl
{
	char				*output;
	char				*input;
	char				*inkey;
	int					decrypt;
	int					pubin;
	int					hexdump;
	t_rsakey			*key;
	__uint64_t			data;
	size_t				length;
}						t_rsautl;

typedef struct			s_rsagen
{
	char				*output;
	char				*random;
}						t_rsagen;

typedef struct			s_rsacmd
{
	char				*output;
	char				*input;
	char				*outform;
	char				*inform;
	char				*passin;
	char				*passout;
	int					pubin;
	int					pubout;
	int					check;
	int					modulus;
	int					noout;
	int					des;
	int					text;
	t_des				*desin;
	t_des				*desout;
	t_rsakey			*key;
}						t_rsacmd;

t_rsakey				*create_rsa_key(int \
						(*is_primary)(__uint64_t, float), float probality);
void					print_rsa_key(t_rsakey *key);
void					check_rsa_key(t_rsakey *key);
t_rsakey				*read_key(int pubin, t_des *des);
void					write_key(t_rsakey *key, int pubout, t_des *des);
t_rsakey				*read_key_der(int pubin);
void					write_key_der(t_rsakey *key, int pubout);
void					check_rsagen(t_sslarg *arg, struct s_command *command);
void					free_rsagen(t_rsagen *cmd);
void					execute_rsagen(struct s_command *command);
void					check_rsacmd(t_sslarg *arg, struct s_command *command);
void					free_rsacmd(t_rsacmd *cmd);
void					execute_rsacmd(struct s_command *command);
void					check_rsautl(t_sslarg *arg, struct s_command *command);
void					free_rsautl(t_rsautl *cmd);
void					execute_rsautl(struct s_command *command);
size_t					write_public_key(t_rsakey *key, char *buff);
void					print_head(int pubout, t_des *des);
t_rsakey				*read_public_key(char *body, \
							size_t (reader)(char*, size_t));
t_rsakey				*read_private_key(char *body, \
							size_t (reader)(char*, size_t));
size_t					write_private_key(t_rsakey *key, char *buff);
t_rsakey				*read_key_body(char *body, int pubin, t_des *des);

#endif
