#include "password.h"
#include "des.h"

char *askPassword(struct s_des *des)
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
			basicError("Verify failure");
		ft_strdel(&p1);
		password = p2;
	}
	if (ft_strlen(password) > PASSWORD_LEN)
	{
		password[PASSWORD_LEN] = '\0';
	}
	return password;
}

void desPassword_encrypt(struct s_des *des)
{
	char *password;
	unsigned int *codeMD5;
	char buff[200];

	if (des->salt)
		des->int64Salt = keyFromString(des->salt);
	else
		randomRead((char*)&des->int64Salt, 8, NULL);
	

	des->generatedKey = 1;
	password = askPassword(des);
	ft_strcpy(buff, password);
	ft_strncat(buff, (char*) &des->int64Salt, 8);
	codeMD5 = hashMD5(buff);
	ft_memcpy(&des->int64Key, codeMD5, 8);
	ft_memcpy(&des->int64Iv, (char*)codeMD5 + 8, 8);
	ft_memdel((void**)&codeMD5);

//	char *dbg;
//	dbg = (char*)&des->int64Salt;
//	ft_printf("SALT => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
//	dbg = (char*)&des->int64Key;
//	ft_printf("KEY => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
//	dbg = (char*)&des->int64Iv;
//	ft_printf("IV => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
}

void desPassword_decrypt(struct s_des *des)
{
	char *password;
	unsigned int *codeMD5;
	char buff[200];
	size_t length;


	if (!des->int64Salt)
	{
		length = readDES(des, buff);
		ft_printf("BUFF = [%.8s] (%zu)\n", buff, length);
		if (length != 8 || ft_strncmp(buff, "Salted__", 8) != 0)
			basicError("Wrong magic");
		length = readDES(des, buff);
		if (length != 8)
			basicError("Wrong magic");
		ft_memcpy(&des->int64Salt, buff, 8);
	}

	des->generatedKey = 1;
	password = askPassword(des);
	ft_strcpy(buff, password);
	ft_strncat(buff, (char*) &des->int64Salt, 8);
	codeMD5 = hashMD5(buff);
	ft_memcpy(&des->int64Key, codeMD5, 8);
	ft_memcpy(&des->int64Iv, (char*)codeMD5 + 8, 8);
	ft_memdel((void**)&codeMD5);

//	char *dbg;
//	dbg = (char*)&des->int64Key;
//	ft_printf("KEY => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
//	dbg = (char*)&des->int64Iv;
//	ft_printf("IV => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
}

void desPassword(struct s_des *des)
{

	if (!des->iv && des->cbc && des->key)
		basicError("iv undefined");
	if (des->key)
	{
		des->int64Key = keyFromString(des->key);
		if (des->iv)
			des->int64Iv = keyFromString(des->iv);
	}
	else
	{
		if (!des->decrypt)
			desPassword_encrypt(des);
		else
			desPassword_decrypt(des);
	}
}
