#include "base64.h"

char	get6Bits(char *bits, int length, int offset)
{
	int		i;
	char	value;
	char*	codes = BASE64_CODE;

	i = 0;
	value = 0;
	if (length >= 6)
		length = 6;
	while (i < length)
	{
		setBit(&value, 2+i, getBit(bits, offset+i));
		i++;
	}
	return codes[(int)value];
}

void	base64encode(char *from,  size_t length, char *to)
{
	size_t i;
	int j;

	i = 0;
	j = 0;
	while (i < length*8)
	{
		to[j] = get6Bits(from, length*8 - i, i);
		i += 6;
		j++;
	}
	while (j % 4 > 0)
	{
		to[j] = '=';
		j++;
	}
}

void	set6bits(char *to, size_t n, size_t offset, char c)
{
	char*	codes = BASE64_CODE;
	char value;
	size_t i;

	value = ft_index(codes, (int)c);
	if (value < 0)
		basicError("wrong character during base64 decoding");
	i = 0;
	if (n > 6)
		n = 6;
	while (i < n)
	{
		setBit(to, offset+i, getBit(&value, 2+i));
		i++;
	}

}

size_t	base64decode(char *from,  size_t length, char *to)
{
	size_t padding;
	size_t i;

	padding = 0;
	if (length > 1 && from[length-1] == '=')
		padding++;
	if (length > 2 && from[length-2] == '=')
		padding++;
	i = 0;
	while (i < length-padding)
	{
		if (i == length-padding - 1 && padding == 1)
			set6bits(to, 4, i*6, from[i]);
		if (i == length-padding - 1 && padding == 2)
			set6bits(to, 2, i*6, from[i]);
		else
			set6bits(to, 6, i*6, from[i]);
		i++;
	}
	return divCeil(length, 4) * 3 - padding;
}
