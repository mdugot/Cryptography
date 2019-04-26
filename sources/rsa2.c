/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:04:51 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 19:06:11 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void		print_end(int pubout)
{
	if (pubout)
		ft_printf_fd(fd_write_access(NULL), \
				"\n-----END RSA PUBLIC KEY-----\n");
	else
		ft_printf_fd(fd_write_access(NULL), \
				"\n-----END RSA PRIVATE KEY-----\n");
}

void		write_key_der(t_rsakey *key, int pubout)
{
	char	buff[1000];
	size_t	length;

	ft_bzero(buff, 1000);
	if (pubout)
		length = write_public_key(key, buff);
	else
		length = write_private_key(key, buff);
	write_to_fd(buff, length);
}

void		write_key(t_rsakey *key, int pubout, t_des *des)
{
	char	buff[1000];
	size_t	length;

	ft_bzero(buff, 1000);
	print_head(pubout, des);
	if (pubout)
		length = write_public_key(key, buff);
	else
		length = write_private_key(key, buff);
	if (des)
	{
		buff_read_access(buff, length);
		des->int_64_iv = des->int_64_salt;
		des_command(des);
	}
	else
		write_to_fd_64(buff, length);
	print_end(pubout);
}

t_rsakey	*read_key_body(char *body, int pubin, t_des *des)
{
	char buff[KEYMAXBODY + 1];

	if (des && des->int_64_salt)
	{
		buff_read_access(body, ft_strlen(body));
		buff_write_access(buff, KEYMAXBODY);
		des_password(des);
		des->int_64_iv = des->int_64_salt;
		des_command(des);
		buff_read_access(buff, KEYMAXBODY);
		if (pubin)
			return (read_public_key(buff, read_from_buff));
		return (read_private_key(buff, read_from_buff));
	}
	else
	{
		if (pubin)
			return (read_public_key(body, read_from_arg_64));
		return (read_private_key(body, read_from_arg_64));
	}
}
