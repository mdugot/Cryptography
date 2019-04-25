/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:32:25 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/25 14:33:42 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "bit.h"
# include "error.h"
# define BUFF64_SIZE 300

# define BASE64_CODE \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"\
	"abcdefghijklmnopqrstuvwxyz"\
	"0123456789+/"

struct s_command;

typedef struct			s_base64
{
	char				*output;
	char				*input;
	int					decrypt;
}						t_base64;

void					base_64_encode(char *from, size_t length, char *to);
size_t					base_64_decode(char *from, size_t length, char *to);
void					execute_64(struct s_command *command);
void					check_64(t_sslarg *arg, struct s_command *command);

#endif
