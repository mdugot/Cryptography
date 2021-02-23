/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:04:47 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 19:07:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

t_rsakey	*read_private_key(char *body, size_t (reader)(char*, size_t))
{
	t_rsakey	*key;
	size_t		length;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	if (body)
		arg_read_access(body);
	check_is_sequence(reader);
	length = read_length(reader);
	if (pass_data(reader) != 0x02)
	{
		check_is_bits(reader);
		length = read_length(reader);
		check_is_sequence(reader);
		length = read_length(reader);
	}
	read_integer(reader, (char*)&key->modulus, 8);
	read_integer(reader, (char*)&key->public_exponent, 8);
	read_integer(reader, (char*)&key->private_exponent, 8);
	read_integer(reader, (char*)&key->prime1, 8);
	read_integer(reader, (char*)&key->prime2, 8);
	read_integer(reader, (char*)&key->exponent_1, 8);
	read_integer(reader, (char*)&key->exponent_2, 8);
	read_integer(reader, (char*)&key->coefficient, 8);
	return (key);
}

t_rsakey	*read_public_key(char *body, size_t (reader)(char*, size_t))
{
	t_rsakey	*key;
	size_t		length;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	key->public_key = 1;
	if (body)
		arg_read_access(body);
	check_is_sequence(reader);
	length = read_length(reader);
	if (pass_data(reader) != 0x02)
	{
		check_is_bits(reader);
		length = read_length(reader);
		check_is_sequence(reader);
		length = read_length(reader);
	}
	read_integer(reader, (char*)&key->modulus, 8);
	read_integer(reader, (char*)&key->public_exponent, 8);
	// print_rsa_key(key);
	return (key);
}

size_t		write_public_key(t_rsakey *key, char *buff)
{
	size_t length;

	length = 0;
	write_sequence(buff, DER_VERSION + 9 + 3, &length);
	write_version(buff, &length);
	write_integer(buff, key->modulus, &length, 9);
	write_integer(buff, key->public_exponent, &length, 3);
	return (length);
}

size_t		write_private_key(t_rsakey *key, char *buff)
{
	size_t length;

	length = 0;
	write_sequence(buff, \
			DER_VERSION + 9 + 3 + 8 + 5 + 5 + 4 + 4 + 4 + 8 * 2, &length);
	write_version(buff, &length);
	write_integer(buff, key->modulus, &length, 9);
	write_integer(buff, key->public_exponent, &length, 3);
	write_integer(buff, key->private_exponent, &length, 8);
	write_integer(buff, key->prime1, &length, 5);
	write_integer(buff, key->prime2, &length, 5);
	write_integer(buff, key->exponent_1, &length, 4);
	write_integer(buff, key->exponent_2, &length, 4);
	write_integer(buff, key->coefficient, &length, 4);
	return (length);
}

void		print_head(int pubout, t_des *des)
{
	unsigned long int salt;

	if (pubout)
		ft_printf_fd(fd_write_access(NULL), \
				"-----BEGIN RSA PUBLIC KEY-----\n");
	else
		ft_printf_fd(fd_write_access(NULL), \
				"-----BEGIN RSA PRIVATE KEY-----\n");
	if (des)
	{
		des_password(des);
		salt = des->int_64_salt;
		reverse_endian((char*)&salt, 8);
		ft_printf_fd(fd_write_access(NULL), "Proc-Type: 4,ENCRYPTED\n");
		ft_printf_fd(fd_write_access(NULL), \
				"DEK-Info: DES-CBC,%016llX\n\n", salt);
	}
}
