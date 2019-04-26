/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:39:29 by mdugot            #+#    #+#             */
/*   Updated: 2019/04/26 15:58:12 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

__int64_t	gcd_extended(__uint64_t a, __uint64_t b, __int64_t *x, __int64_t *y)
{
	__int64_t x1;
	__int64_t y1;
	__int64_t gcd;

	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return (b);
	}
	gcd = gcd_extended(b % a, a, &x1, &y1);
	*x = ((__uint64_t)y1 - (b / a) * (__uint64_t)x1);
	*y = x1;
	return (gcd);
}

int			is_coprime(__uint64_t n1, __uint64_t n2)
{
	__uint64_t i;

	i = 2;
	while (i <= n2)
	{
		if (i % n1 == 0 && i % n2 == 0)
			return (0);
		i++;
	}
	return (1);
}

void		random_prime_pair(t_rsakey *key, \
			int (*is_primary)(__uint64_t, float), float probability)
{
	key->prime1 = 0;
	while (key->prime1 == 0 || !is_primary(key->prime1, probability))
		key->prime1 = random_int_64(RANDMIN, RANDMAX);
	key->prime2 = 0;
	while (key->prime2 == 0
		|| !is_primary(key->prime2, probability)
		|| !is_coprime((key->prime1 - 1) * (key->prime2 - 1), \
						key->public_exponent))
		key->prime2 = random_int_64(RANDMIN, RANDMAX);
}

t_rsakey	*create_rsa_key(int (*is_primary)(__uint64_t, float), \
			float probability)
{
	t_rsakey	*key;
	__uint64_t	phi;
	__int64_t	x;
	__int64_t	y;
	__int64_t	r;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	key->public_exponent = 65537;
	random_prime_pair(key, is_primary, probability);
	ft_printf("e is 65537 (0x10001)\n");
	phi = (key->prime1 - 1) * (key->prime2 - 1);
	r = gcd_extended(key->public_exponent, phi, &x, &y);
	key->private_exponent = (__uint64_t)(x < 0 ? (phi + x) : x);
	key->modulus = key->prime1 * key->prime2;
	key->exponent_1 = key->private_exponent % (key->prime1 - 1);
	key->exponent_2 = key->private_exponent % (key->prime2 - 1);
	key->coefficient = modular_pow(key->prime2, key->prime1 - 2, key->prime1);
	return (key);
}

void		print_rsa_key(t_rsakey *key)
{
	ft_printf("Private-Key: (64 bit)\n");
	ft_printf("modulus: %lld (%#llx)\n", key->modulus, key->modulus);
	ft_printf("public_exponent: %lld (%#llx)\n", \
			key->public_exponent, key->public_exponent);
	ft_printf("private_exponent: %lld (%#llx)\n", \
			key->private_exponent, key->private_exponent);
	ft_printf("prime1: %lld (%#llx)\n", key->prime1, key->prime1);
	ft_printf("prime2: %lld (%#llx)\n", key->prime2, key->prime2);
	ft_printf("exponent1: %lld (%#llx)\n", key->exponent_1, key->exponent_1);
	ft_printf("exponent2: %lld (%#llx)\n", key->exponent_2, key->exponent_2);
	ft_printf("coefficient: %lld (%#llx)\n", \
			key->coefficient, key->coefficient);
}

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
	ft_printf("sequence length = %llx\n", length);
	if (pass_data(reader) != 0x02)
	{
		ft_printf("PASS\n");
		check_is_bits(reader);
		length = read_length(reader);
		check_is_sequence(reader);
		length = read_length(reader);
		ft_printf("END PASS\n");
	}
	ft_printf("modulus\n");
	read_integer(reader, (char*)&key->modulus, 8);
	ft_printf("public e\n");
	read_integer(reader, (char*)&key->public_exponent, 8);
	ft_printf("ok\n");
	print_rsa_key(key);
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
	char	buff[1000] = {0};
	size_t	length;

	if (pubout)
		length = write_public_key(key, buff);
	else
		length = write_private_key(key, buff);
	write_to_fd(buff, length);
}

void		write_key(t_rsakey *key, int pubout, t_des *des)
{
	char	buff[1000] = {0};
	size_t	length;

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

t_rsakey	*read_key_der(int pubin)
{
	if (pubin)
		return (read_public_key(NULL, read_from_fd));
	return (read_private_key(NULL, read_from_fd));
}

t_rsakey	*read_key(int pubin, t_des *des)
{
	char	*line;
	char	body[KEYMAXBODY + 1];
	int		end;
	char	*salt;

	end = -1;
	body[0] = 0;
	line = NULL;
	while (end < 1)
	{
		if (get_next_line(fd_read_access(NULL), &line) <= 0)
			basic_error("error when reading rsa pem key");
		if (end < 0 &&
			ft_strstr(line, "-----BEGIN") == line &&
			line + ft_strlen(line) - ft_strstr(line, "KEY-----") == 8)
		{
			end = 0;
		}
		else if (ft_strlen(line) == 0 ||
				ft_strstr(line, "Proc-Type: 4,ENCRYPTED") == line)
		{
		}
		else if (end == 0 && ft_strstr(line, "DEK-Info: DES-CBC,") == line)
		{
			salt = line + ft_strlen("DEK-Info: DES-CBC,");
			if (ft_strlen(salt) != 16)
				basic_error("pem wrong salt format");
			des->int_64_salt = key_from_string(salt);
		}
		else if (end == 0 &&
			ft_strstr(line, "-----END") == line &&
			line + ft_strlen(line) - ft_strstr(line, "KEY-----") == 8)
		{
			end = 1;
		}
		else if (end == 0)
		{
			if (ft_strlen(body) + ft_strlen(line) >= KEYMAXBODY)
				basic_error("pem key wrong format");
			ft_strcat(body, line);
		}
		else
			basic_error("pem key wrong format");
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
