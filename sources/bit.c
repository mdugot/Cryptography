#include "bit.h"

char bitMask(int idx)
{
	char mask;
	int i = 7;

	mask = 1;
	while(i > idx)
	{
		mask *= 2;
		i--;
	}
	return mask;
}

void setBit(char *bytes, int idx, char bit)
{
	char mask;

	mask = bitMask(idx % 8);
	idx = idx / 8;
	if (bit)
		bytes[idx] = bytes[idx] | mask;
	else
		bytes[idx] = bytes[idx] & (0xFF ^ mask);
}

char getBit(char *bytes, int idx)
{
	char mask;

	mask = bitMask(idx % 8);
	idx = idx / 8;
//	ft_printf("byte idx %d\n", idx);
//	ft_printf("%08hhb get (%08hhb) = %d\n", bytes[idx], mask, (bytes[idx] & mask) ? 1 : 0);
	return (bytes[idx] & mask) ? 1 : 0;
}
