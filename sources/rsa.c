#include "rsa.h"

__int64_t gcdExtended(__uint64_t a, __uint64_t b, __int64_t *x,  __int64_t *y)
{
   // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    __int64_t x1, y1; // To store results of recursive call 
    __int64_t gcd = gcdExtended(b%a, a, &x1, &y1); 
    // Update x and y using results of recursive 
    // call 
    *x = ((__uint64_t)y1 - (b/a) * (__uint64_t)x1);
    *y = x1; 
  
    return gcd;
}

int isCoprime(__uint64_t n1, __uint64_t n2)
{
	__uint64_t i;
	i = 2;
	while (i <= n2)
	{
		if (i % n1 == 0 && i % n2 == 0)
			return 0;
		i++;
	}
	return 1;
}

void	randomPrimePair(t_rsakey *key, int (*isPrimary)(__uint64_t, float), float probability)
{
	key->prime1 = 0;
	while (key->prime1 == 0 || !isPrimary(key->prime1, probability))
		key->prime1 = randomInt64(RANDMIN, RANDMAX);
	key->prime2 = 0;
	while (key->prime2 == 0
		|| !isPrimary(key->prime2, probability)
		|| !isCoprime((key->prime1-1) * (key->prime2-1), key->publicExponent))
		key->prime2 = randomInt64(RANDMIN, RANDMAX);
}

t_rsakey	*createRsaKey(int (*isPrimary)(__uint64_t, float), float probability)
{
	t_rsakey	*key;
	__uint64_t phi;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	key->publicExponent =  65537;
	randomPrimePair(key, isPrimary, probability);
	ft_printf("e is 65537 (0x10001)\n");
	phi = (key->prime1-1) * (key->prime2-1);

	__int64_t x;
	__int64_t y;
	__int64_t r;
	r = gcdExtended(key->publicExponent, phi, &x, &y);
	key->privateExponent = (__uint64_t)(x < 0 ? (phi + x) : x);
	key->modulus = key->prime1*key->prime2;
	key->exponent1 = key->privateExponent % (key->prime1 -1);
	key->exponent2 = key->privateExponent % (key->prime2 -1);
	key->coefficient = modularPow(key->prime2, key->prime1 - 2, key->prime1);
	return key;
}

void	printRsaKey(t_rsakey *key)
{
	ft_printf("Private-Key: (64 bit)\n");
	ft_printf("modulus: %lld (%#llx)\n", key->modulus, key->modulus);
	ft_printf("publicExponent: %lld (%#llx)\n", key->publicExponent, key->publicExponent);
	ft_printf("privateExponent: %lld (%#llx)\n", key->privateExponent, key->privateExponent);
	ft_printf("prime1: %lld (%#llx)\n", key->prime1, key->prime1);
	ft_printf("prime2: %lld (%#llx)\n", key->prime2, key->prime2);
	ft_printf("exponent1: %lld (%#llx)\n", key->exponent1, key->exponent1);
	ft_printf("exponent2: %lld (%#llx)\n", key->exponent2, key->exponent2);
	ft_printf("coefficient: %lld (%#llx)\n", key->coefficient, key->coefficient);
}

t_rsakey	*readPrivateKey(char *body, size_t (reader)(char*, size_t))
{
	t_rsakey	*key;
	size_t length;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	if (body)
		argReadAccess(body);
	checkIsSequence(reader);
	length = readLength(reader);
	if (passData(reader) != 0x02)
	{
		checkIsBits(reader);
		length = readLength(reader);
		checkIsSequence(reader);
		length = readLength(reader);
	}
	readInteger(reader, (char*)&key->modulus, 8);
	readInteger(reader, (char*)&key->publicExponent, 8);
	readInteger(reader, (char*)&key->privateExponent, 8);
	readInteger(reader, (char*)&key->prime1, 8);
	readInteger(reader, (char*)&key->prime2, 8);
	readInteger(reader, (char*)&key->exponent1, 8);
	readInteger(reader, (char*)&key->exponent2, 8);
	readInteger(reader, (char*)&key->coefficient, 8);
	//printRsaKey(key);
	return key;
}

t_rsakey	*readPublicKey(char *body, size_t (reader)(char*, size_t))
{
	t_rsakey	*key;
	size_t length;

	key = ft_memalloc(sizeof(t_rsakey));
	ft_bzero(key, sizeof(t_rsakey));
	key->publicKey = 1;
	if (body)
		argReadAccess(body);
	checkIsSequence(reader);
	length = readLength(reader);
	ft_printf("sequence length = %llx\n", length);
	if (passData(reader) != 0x02)
	{
		ft_printf("PASS\n");
		checkIsBits(reader);
		length = readLength(reader);
		checkIsSequence(reader);
		length = readLength(reader);
		ft_printf("END PASS\n");
	}
	ft_printf("modulus\n");
	readInteger(reader, (char*)&key->modulus, 8);
	ft_printf("public e\n");
	readInteger(reader, (char*)&key->publicExponent, 8);
	ft_printf("ok\n");
	printRsaKey(key);
	return key;
}

size_t	writePublicKey(t_rsakey	*key, char *buff)
{
	size_t length;

	length = 0;
	writeSequence(buff, DER_VERSION + 9 + 3, &length);
	writeVersion(buff, &length);
	writeInteger(buff, key->modulus, &length, 9);
	writeInteger(buff, key->publicExponent, &length, 3);
	return length;
}

size_t	writePrivateKey(t_rsakey	*key, char *buff)
{
	size_t length;

	length = 0;
	writeSequence(buff, DER_VERSION + 9 + 3 + 8 + 5 + 5 + 4 + 4 + 4 + 8*2, &length);
	writeVersion(buff, &length);
	writeInteger(buff, key->modulus, &length, 9);
	writeInteger(buff, key->publicExponent, &length, 3);
	writeInteger(buff, key->privateExponent, &length, 8);
	writeInteger(buff, key->prime1, &length, 5);
	writeInteger(buff, key->prime2, &length, 5);
	writeInteger(buff, key->exponent1, &length, 4);
	writeInteger(buff, key->exponent2, &length, 4);
	writeInteger(buff, key->coefficient, &length, 4);
	return length;
}

void printHead(int pubout, t_des *des)
{
	unsigned long int salt;

	if (pubout)
		ft_printf_fd(fdWriteAccess(NULL), "-----BEGIN RSA PUBLIC KEY-----\n");
	else
		ft_printf_fd(fdWriteAccess(NULL), "-----BEGIN RSA PRIVATE KEY-----\n");
	if (des)
	{
		desPassword(des);
		salt = des->int64Salt;
		reverseEndian((char*)&salt, 8);
		ft_printf_fd(fdWriteAccess(NULL), "Proc-Type: 4,ENCRYPTED\n");
		ft_printf_fd(fdWriteAccess(NULL), "DEK-Info: DES-CBC,%016llX\n\n", salt);
	}
}

void printEnd(int pubout)
{
	if (pubout)
		ft_printf_fd(fdWriteAccess(NULL), "\n-----END RSA PUBLIC KEY-----\n");
	else
		ft_printf_fd(fdWriteAccess(NULL), "\n-----END RSA PRIVATE KEY-----\n");
}

void	writeKeyDER(t_rsakey *key, int pubout)
{
	char buff[1000] = {0};
	size_t length;
	if (pubout)
		length = writePublicKey(key, buff);
	else
		length = writePrivateKey(key, buff);
	writeToFd(buff, length);
}

void	writeKey(t_rsakey *key, int pubout, t_des *des)
{
	char buff[1000] = {0};
	size_t length;

	printHead(pubout, des);
	if (pubout)
		length = writePublicKey(key, buff);
	else
		length = writePrivateKey(key, buff);
	if (des)
	{
		buffReadAccess(buff, length);
		des->int64Iv = des->int64Salt;
		DES(des);
	}
	else
		writeToFd64(buff, length);
	printEnd(pubout);
}

t_rsakey	*readKeyBody(char *body, int pubin, t_des *des)
{
	char buff[KEYMAXBODY+1];

	if (des && des->int64Salt)
	{
		buffReadAccess(body, ft_strlen(body));
		buffWriteAccess(buff, KEYMAXBODY);
		desPassword(des);
		des->int64Iv = des->int64Salt;
		DES(des);
		buffReadAccess(buff, KEYMAXBODY);
		if (pubin)
			return readPublicKey(buff, readFromBuff);
		return readPrivateKey(buff, readFromBuff);
	}
	else
	{
		if (pubin)
			return readPublicKey(body, readFromArg64);
		return readPrivateKey(body, readFromArg64);
	}
}

t_rsakey	*readKeyDER(int pubin)
{
		if (pubin)
			return readPublicKey(NULL, readFromFd);
		return readPrivateKey(NULL, readFromFd);
}

t_rsakey	*readKey(int pubin, t_des *des)
{
	char *line;
	char body[KEYMAXBODY+1];
	int end;
	char *salt;

	end = -1;
	body[0] = 0;
	line = NULL;
	while (end < 1)
	{
		if (get_next_line(fdReadAccess(NULL), &line) <= 0)
			basicError("error when reading rsa pem key");
		if (end < 0 &&
			ft_strstr(line, "-----BEGIN") == line &&
			line + ft_strlen(line) - ft_strstr(line, "KEY-----") == 8)
		{
			end = 0;
		}
		else if (ft_strlen(line) == 0 || ft_strstr(line, "Proc-Type: 4,ENCRYPTED") == line)
		{
		}
		else if (end == 0 && ft_strstr(line, "DEK-Info: DES-CBC,") == line)
		{
			salt = line + ft_strlen("DEK-Info: DES-CBC,");
			if (ft_strlen(salt) != 16)
				basicError("pem wrong salt format");
			des->int64Salt = keyFromString(salt);
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
				basicError("pem key wrong format");
			ft_strcat(body, line);
		}
		else
			basicError("pem key wrong format");
	}
	ft_strdel(&line);
	return readKeyBody(body, pubin, des);
}

void checkRsaKey(t_rsakey *key)
{
	if (key->publicExponent * key->publicExponent % 2 != 1)
		rsaError("d e is not congruent to 1");
	if (key->publicExponent % 2 != 1)
		rsaError("e is not odd");
	if (key->modulus % 2 != 1)
		rsaError("n is not odd");
	if (key->prime1 % 2 != 1)
		rsaError("p is not odd");
	if (key->prime2 % 2 != 1)
		rsaError("q is not odd");
	if (key->prime1 * key->prime2 != key->modulus)
		rsaError("n does not equal p q");
	if ((key->exponent1 * key->publicExponent) % (key->prime1 - 1) != 1)
		rsaError("1 is does not equal (dp e) mod (p - 1)");
	if ((key->exponent2 * key->publicExponent) % (key->prime2 - 1) != 1)
		rsaError("1 is does not equal (dq e) mod (q - 1)");
	if (key->exponent1 != key->privateExponent % (key->prime1 -1))
		rsaError("dp does not equal d mod (p - 1)");
	if (key->exponent2 != key->privateExponent % (key->prime2 -1))
		rsaError("dq does not equal d mod (p - 1)");
	if (key->coefficient >= key->prime1)
		rsaError("qinv greater than p");
	rsaError(NULL);
	ft_printf("RSA key ok\n");
}
