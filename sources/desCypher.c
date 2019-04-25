#include "des.h"

void permutation(char *from,  char *to, int *permutationTable, int length)
{
	int i = 0;
	int pi;

	while (i < length)
	{
		pi = permutationTable[i] - 1;
//		ft_printf("Permatutate %d <- %d\n", i, pi);
//		ft_printf("%d is %d\n", pi, getBit(from, pi));
		setBit(to, i, getBit(from, pi));
		i++;
	}
}

void printBits(char *message, char *bytes, int length)
{
	int i;

	i = 0;
	ft_printf("%s :", message);
	while (i < length)
	{
		ft_printf(" %08hhb", bytes[i]);
		i++;
	}
	ft_putendl("");
}

void subkey(char* key, char* cd)
{
	int pc2[56] = {PC2};

//	ft_printf("CD : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", cd[0], cd[1], cd[2], cd[3], cd[4], cd[5], cd[6]);
	permutation(cd, key, pc2, 48);
//	ft_printf("KEY : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", key[0], key[1], key[2], key[3], key[4], key[5]);
}

void cd16(char *pkey, char keys[16][6], char decrypt)
{
	int shift[16] = {CD16_SHIFT};
	char cd[16][7];
	char *last = pkey;
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 28)
		{
			setBit(cd[i], j, getBit(last, (j+shift[i])%28));
			j++;
		}
		j = 0;
		while (j < 28)
		{
			setBit(cd[i], 28+j, getBit(last, 28+(j+shift[i])%28));
			j++;
		}
		last = cd[i];
		subkey(keys[(decrypt ? (15-i) : i)], cd[i]);
		i++;
	}
}

void prepareKeys(unsigned long int key, char keys[16][6], char decrypt)
{
	int pc1[56] = {PC1};
	char pkey[7];

//	reverseEndian((char*)&key, 8);
	permutation((char*)&key, pkey, pc1, 56);
//	printBits("DEBUG", pkey, 7);
	cd16(pkey, keys, decrypt);
}

int getSboxValue(char *bytes, int table, int offset)
{
	int sbox[64*8] = {SBOX};
	char x;
	char y;

	x = 0;
	y = 0;
	setBit(&y, 6, getBit(bytes, offset));
	setBit(&y, 7, getBit(bytes, offset+5));
	setBit(&x, 4, getBit(bytes, offset+1));
	setBit(&x, 5, getBit(bytes, offset+2));
	setBit(&x, 6, getBit(bytes, offset+3));
	setBit(&x, 7, getBit(bytes, offset+4));
//	ft_printf("x = %hhd, y = %hhd\n", x, y);
	return sbox[64*table+y*16+x];
}

int fperm(int result)
{
	int ftable[32] = {FTABLE};
	int presult;

	presult = 0;
	reverseEndian((char*)&result, 4);
	permutation((char*)&result, (char*)&presult, ftable, 32);
//	char *dbg = (char*)&presult;
//	ft_printf("presult : %08hhb %08hhb %08hhb %08hhb\n", dbg[0], dbg[1], dbg[2], dbg[3]);
	return presult;
}

int function(char *rightHalf, char *key)
{
	char tmp[6];
	int etable[64] = {ETABLE};
	int i;
	int boxValue;
	int result;

	permutation(rightHalf, tmp, etable, 48);
	i = 0;
	while (i < 6)
	{
		tmp[i] = tmp[i] ^ key[i];
		i++;
	}
//	ft_printf("K^pR0 : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
	i = 0;
	result = 0;
	while (i < 8)
	{
		boxValue = getSboxValue(tmp, i, i*6);
//		ft_printf("box value %2d : %04b\n", i, boxValue);
		result = (result << 4) | boxValue;
//		char *dbg = (char*)&result;
//		ft_printf("result %2d : %08hhb %08hhb %08hhb %08hhb\n", i, dbg[0], dbg[1], dbg[2], dbg[3]);
		i++;
	}
	return fperm(result);
}

unsigned long int mergeLR(int l, int r)
{
	int ip1[64] = {IP_1};
	unsigned long int result;
	unsigned long int presult;

	result = 0;
	ft_memcpy(&result, &r, 4);
	ft_memcpy(((char*)&result)+4, &l, 4);

	char *dbg;
	dbg = (char*)&result;
//	ft_printf("Merge : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);

	permutation((char*)&result, (char*)&presult, ip1, 64);
	dbg = (char*)&presult;
//	ft_printf("pMerge : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);

	return presult;
}

unsigned long int encodeMessage(unsigned long int message, char keys[16][6])
{
	int ip[64] = {IP};
	char pmessage[8];
	int i;
	int r[17];
	int l[17];

	(void)keys;
	//reverseEndian((char*)&message, 8);
	permutation((char*)&message, pmessage, ip, 64);
//	ft_printf("pm : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", pmessage[0], pmessage[1], pmessage[2], pmessage[3], pmessage[4], pmessage[5], pmessage[6], pmessage[7]);

	ft_memcpy(&r[0], pmessage+4, 4);
	ft_memcpy(&l[0], pmessage, 4);

	char *dbg;
	dbg = (char*)&r[0];
//	ft_printf("r0 : %08hhb %08hhb %08hhb %08hhb\n", dbg[0], dbg[1], dbg[2], dbg[3]);
	dbg = (char*)&l[0];
//	ft_printf("l0 : %08hhb %08hhb %08hhb %08hhb\n", dbg[0], dbg[1], dbg[2], dbg[3]);
	i = 1;
	while (i < 17)
	{
		r[i] = l[i-1] ^ function((char*)&r[i-1], keys[i-1]);
		l[i] = r[i-1];
		dbg = (char*)&r[i];
//		ft_printf("\nr%d : %08hhb %08hhb %08hhb %08hhb\n", i, dbg[0], dbg[1], dbg[2], dbg[3]);
		dbg = (char*)&l[i];
//		ft_printf("l%d : %08hhb %08hhb %08hhb %08hhb\n", i, dbg[0], dbg[1], dbg[2], dbg[3]);
		i++;
	}
	return mergeLR(l[16], r[16]);
}



unsigned long int des(unsigned long int message, size_t length, t_des *cmd)
{
	unsigned long int result;
	char keys[16][6];

	if (!cmd->decrypt && length < 8)
		pkcs((char*)&message, 8, length);
	if (!cmd->decrypt && cmd->cbc)
		message = message ^ cmd->int64Iv;
	prepareKeys(cmd->int64Key, keys, cmd->decrypt);
//	ft_printf("KEY : %08hhb %08hhb %08hhb %08hhb %08hhb %08hhb\n", keys[13][0], keys[13][1], keys[13][2], keys[13][3], keys[13][4], keys[13][5]);
	result = encodeMessage(message, keys);
//	ft_printf("FINAL RESULT : %016llX\n", result);
//	char *dbg;
//	dbg = (char*)&result;
//ft_printf("HEXA CODE => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);

	if (cmd->decrypt && cmd->cbc)
		result = result ^ cmd->int64Iv;
	return result;
}

