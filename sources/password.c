/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:19:27 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 14:26:08 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "password.h"
#include "des.h"

char	*ask_password(struct s_des *des)
{
	char *p1;
	char *p2;
	char *password;

	if (des->password)
		password = des->password;
	else
	{
		p1 = ft_strdup(getpass("enter encryption password: "));
		p2 = getpass("Verifying - enter encryption password: ");
		if (ft_strcmp(p1, p2) != 0)
			basic_error("Verify failure");
		ft_strdel(&p1);
		password = p2;
	}
	if (ft_strlen(password) > PASSWORD_LEN)
	{
		password[PASSWORD_LEN] = '\0';
	}
	return (password);
}

void	des_password_encrypt(struct s_des *des)
{
	char			*password;
	unsigned int	*code_md5;
	char			buff[200];

	if (des->salt)
		des->int_64_salt = key_from_string(des->salt);
	else
		random_read((char*)&des->int_64_salt, 8, NULL);
	des->generated_key = 1;
	password = ask_password(des);
	ft_strcpy(buff, password);
	ft_strncat(buff, (char*)&des->int_64_salt, 8);
	code_md5 = hash_md5(buff);
	ft_memcpy(&des->int_64_key, code_md5, 8);
	ft_memcpy(&des->int_64_iv, (char*)code_md5 + 8, 8);
	ft_memdel((void**)&code_md5);
}

void	des_password_decrypt(struct s_des *des)
{
	char			*password;
	unsigned int	*code_md5;
	char			buff[200];
	size_t			length;

	if (!des->int_64_salt)
	{
		length = read_des(des, buff);
		ft_printf("BUFF = [%.8s] (%zu)\n", buff, length);
		if (length != 8 || ft_strncmp(buff, "Salted__", 8) != 0)
			basic_error("Wrong magic");
		length = read_des(des, buff);
		if (length != 8)
			basic_error("Wrong magic");
		ft_memcpy(&des->int_64_salt, buff, 8);
	}
	des->generated_key = 1;
	password = ask_password(des);
	ft_strcpy(buff, password);
	ft_strncat(buff, (char*)&des->int_64_salt, 8);
	code_md5 = hash_md5(buff);
	ft_memcpy(&des->int_64_key, code_md5, 8);
	ft_memcpy(&des->int_64_iv, (char*)code_md5 + 8, 8);
	ft_memdel((void**)&code_md5);
}

void	des_password(struct s_des *des)
{
	if (!des->iv && des->cbc && des->key)
		basic_error("iv undefined");
	if (des->key)
	{
		des->int_64_key = key_from_string(des->key);
		if (des->iv)
			des->int_64_iv = key_from_string(des->iv);
	}
	else
	{
		if (!des->decrypt)
			des_password_encrypt(des);
		else
			des_password_decrypt(des);
	}
}
