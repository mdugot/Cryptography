/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:04:34 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 17:02:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H
# include "hexa.h"
# include "check.h"
# include "writer.h"
# include "bit.h"
# include "base64.h"
# include "password.h"

struct s_command;

typedef struct			s_des
{
	char				*password;
	char				*salt;
	unsigned long int	int_64_salt;
	char				*key;
	unsigned long int	int_64_key;
	char				*iv;
	unsigned long int	int_64_iv;
	int					rsa;

	char				*output;
	char				*input;
	int					decrypt;
	int					base_64;
	int					cbc;
	int					generated_key;
	size_t				(*reader)(char*, size_t);
	void				(*writer)(char*, size_t);
}						t_des;

unsigned long int		des(unsigned long int m, size_t l, t_des *des);
void					check_des(t_sslarg *arg, struct s_command *command);
void					free_des(t_des *digest);
size_t					read_des(t_des *cmd, char *buff);
void					execute_des(struct s_command *command);
void					des_command(t_des *cmd);

#endif
