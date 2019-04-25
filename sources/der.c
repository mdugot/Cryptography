#include "der.h"

char nextNoneZero(size_t (reader)(char*, size_t))
{
	char byte;
	size_t r;

	byte = 0;
	while (byte == 0)
	{
		r = reader(&byte, 1);
		if (r < 1)
			basicError("wrong der format : end of file");
	}
	return byte;
}

void checkIsSequence(size_t (reader)(char*, size_t))
{
	char byte;

	byte = nextNoneZero(reader);
	if (byte != 0x30)
		basicError("wrong der format : sequence not found");
}

void checkIsBits(size_t (reader)(char*, size_t))
{
	char byte;

	byte = nextNoneZero(reader);
	if (byte != 0x03)
		basicError("wrong der format : bits string not found");
}

size_t readLength(size_t (reader)(char*, size_t))
{
	char byte;
	char nbytes;
	size_t length;

	if (reader(&byte, 1) != 1)
		basicError("wrong der format : length not found");
	if (!(byte & 0x80))
		return (byte);
	nbytes = byte ^ 0x80;
	if ((size_t)nbytes > sizeof(size_t))
		basicError("wrong der format : length too big");
	if (reader((char*)&length, nbytes) != (size_t)nbytes)
		basicError("wrong der format : unable to read length");
	reverseEndian((char*)&length, nbytes);
	return length;
}

size_t skipZero(size_t (reader)(char*, size_t), size_t expectedLength, size_t realLength)
{
	char byte;
	size_t r;

	while (realLength > expectedLength)
	{
		r = reader(&byte, 1);
		if (r != 1 || byte != 0x0)
			basicError("wrong der format : length too big");
		realLength--;
	}
	return realLength;
}

void readInteger(size_t (reader)(char*, size_t), char *integer, size_t length)
{
	char byte;
	size_t r;

	r = reader(&byte, 1);
	if (r != 1 || byte != 0x02)
		basicError("wrong der format : integer not found");
	r = readLength(reader);
//	ft_printf("integer length = %llx\n", r);
	r = skipZero(reader, length, r);
	if (reader(integer, r) != r)
		basicError("wrong der format : unable to read integer");
	reverseEndian(integer, r);
}

char passData(size_t (reader)(char*, size_t))
{
	char byte;
	char buff[1001];
	size_t r;

	r = reader(&byte, 1);
	r = readLength(reader);
	if (r >= 1000)
		basicError("wrong der format : too many data to pass");
	if (reader(buff, r) != r)
		basicError("wrong der format : unable to read integer");
	return byte;
}

void append(char *buff, char *content, size_t length, size_t *len)
{
	size_t i;
	size_t from;

	i = 0;
	from = *len;
	while (i < length)
	{
		buff[from+i] = content[i];
		i++;
		*len = *len + 1;
	}
}

void writeSequence(char *buff, char length, size_t *len)
{
	char byte;

	if (length >= 127)
		basicError("wrong der format : too long sequence to write");
	byte = 0x30;
	append(buff, &byte, 1, len);
	append(buff, &length, 1, len);
}

void writeInteger(char *buff, __uint64_t integer, size_t *len, size_t expectedLength)
{
	char byte;
	size_t i;

	byte = 0x02;
	append(buff, &byte, 1, len);
	byte = expectedLength;
	append(buff, &byte, 1, len);
	i = 8;
	byte = 0;
	while (i < expectedLength)
	{
		append(buff, &byte, 1, len);
		i++;
	}
	reverseEndian((char*)&integer, 8);
	i = 0;
	if (expectedLength < 8)
		i = 8 - expectedLength;
	append(buff, (char*)&integer+i, 8-i, len);
}

void writeVersion(char *buff, size_t *len)
{
	char byte;

	byte = 0x02;
	append(buff, &byte, 1, len);
	byte = 0x01;
	append(buff, &byte, 1, len);
	byte = 0x00;
	append(buff, &byte, 1, len);
}
