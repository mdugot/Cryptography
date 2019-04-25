#include "hexa.h"


unsigned long int	keyFromString(char *str)
{
	unsigned long int result;
	int pad;

	if (ft_strlen(str) > 16)
		str[16] = 0;
	ft_strupper(str);
	result = ft_hexa(str);
	pad = 0;
	while (ft_strlen(str) + pad < 16)
	{
		result *= 16;
		pad++;
	}
	char *dbg;
	dbg = (char*)&result;
	reverseEndian((char*)&result, 8);
//	ft_printf("rKEY => %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", dbg[0], dbg[1], dbg[2], dbg[3], dbg[4], dbg[5], dbg[6], dbg[7]);
	return result;
}
