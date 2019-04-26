/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:39:29 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 19:08:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

t_rsakey	*read_key_der(int pubin)
{
	if (pubin)
		return (read_public_key(NULL, read_from_fd));
	return (read_private_key(NULL, read_from_fd));
}

void		read_key_salt(t_des *des, char *line)
{
	char	*salt;

	salt = line + ft_strlen("DEK-Info: DES-CBC,");
	if (ft_strlen(salt) != 16)
		basic_error("pem wrong salt format");
	des->int_64_salt = key_from_string(salt);
}

int			read_key_format(t_des *des, char *line, char *body, int end)
{
	if (end < 0 && ft_strstr(line, "-----BEGIN") == line &&
		line + ft_strlen(line) - ft_strstr(line, "KEY-----") == 8)
		return (0);
	else if (ft_strlen(line) == 0 ||
			ft_strstr(line, "Proc-Type: 4,ENCRYPTED") == line)
		return (end);
	else if (end == 0 && ft_strstr(line, "DEK-Info: DES-CBC,") == line)
		read_key_salt(des, line);
	else if (end == 0 && ft_strstr(line, "-----END") == line &&
		line + ft_strlen(line) - ft_strstr(line, "KEY-----") == 8)
		return (1);
	else if (end == 0)
	{
		if (ft_strlen(body) + ft_strlen(line) >= KEYMAXBODY)
			basic_error("pem key wrong format");
		ft_strcat(body, line);
	}
	else
		basic_error("pem key wrong format");
	return (end);
}

t_rsakey	*read_key(int pubin, t_des *des)
{
	char	*line;
	char	body[KEYMAXBODY + 1];
	int		end;

	end = -1;
	body[0] = 0;
	line = NULL;
	while (end < 1)
	{
		if (get_next_line(fd_read_access(NULL), &line) <= 0)
			basic_error("error when reading rsa pem key");
		end = read_key_format(des, line, body, end);
	}
	ft_strdel(&line);
	return (read_key_body(body, pubin, des));
}

void		check_rsa_key(t_rsakey *key)
{
	if (key->public_exponent * key->public_exponent % 2 != 1)
		rsa_error("d e is not congruent to 1");
	if (key->public_exponent % 2 != 1)
		rsa_error("e is not odd");
	if (key->modulus % 2 != 1)
		rsa_error("n is not odd");
	if (key->prime1 % 2 != 1)
		rsa_error("p is not odd");
	if (key->prime2 % 2 != 1)
		rsa_error("q is not odd");
	if (key->prime1 * key->prime2 != key->modulus)
		rsa_error("n does not equal p q");
	if ((key->exponent_1 * key->public_exponent) % (key->prime1 - 1) != 1)
		rsa_error("1 is does not equal (dp e) mod (p - 1)");
	if ((key->exponent_2 * key->public_exponent) % (key->prime2 - 1) != 1)
		rsa_error("1 is does not equal (dq e) mod (q - 1)");
	if (key->exponent_1 != key->private_exponent % (key->prime1 - 1))
		rsa_error("dp does not equal d mod (p - 1)");
	if (key->exponent_2 != key->private_exponent % (key->prime2 - 1))
		rsa_error("dq does not equal d mod (p - 1)");
	if (key->coefficient >= key->prime1)
		rsa_error("qinv greater than p");
	rsa_error(NULL);
	ft_printf("RSA key ok\n");
}
