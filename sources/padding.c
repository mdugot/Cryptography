#include "padding.h"

char *pad(char *string, long unsigned int size, int *nblock, size_t length)
{
	long unsigned int bitsLen;
	long unsigned int nbits;
	char *result;

	size = size * 8;
	bitsLen = 8 * length;
	nbits = bitsLen;
	if (nbits < 448)
	{
//		ft_printf("#Y\t[ONE BLOCK]#E\n");
		*nblock = 1;
		nbits += 448 - nbits;
	}
	else
	{
//		ft_printf("#Y\t[TWO BLOCK]#E\n");
		*nblock = 2;
		nbits += 448  + (512 - nbits);
	}
	nbits += 64;
	result = ft_memalloc((nbits/8));
	ft_bzero(result, (nbits/8));
	ft_memcpy(result, string, length);
	result[length] = 0x80;
	ft_memcpy((void*)&result[(nbits/8)-8], (void*)&size, 8);
	return result;
}

void	pkcs(char *bytes, size_t blockSize, size_t length)
{
	char fill;
	char i;

	fill = blockSize - length;
	i = 0;
	while (i < fill)
	{
		bytes[length+i] = fill;
		i++;
	}
}

unsigned int leftrotate(unsigned int value, unsigned int shift)
{
	return (value << shift) | (value >> (32 - shift));
}

unsigned int rightrotate(unsigned int value, unsigned int shift)
{
	return (value >> shift) | (value << (32 - shift));
}

void reverseEndian(char *bytes, int length)
{
	char tmp;
	int i;

	i = 0;
	while (i < length/2)
	{
		tmp = bytes[i];
		bytes[i] = bytes[length-(i+1)];
		bytes[length-(i+1)] = tmp;
		i++;
	}
}
