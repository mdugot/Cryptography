#include "reader.h"

int 			fdReadAccess(char *filename)
{
	static int fd = 0;
	if (filename != NULL)
	{
		if (fd != 0)
			close(fd);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			wrongFile(filename, "can not open file");
	}
	return fd;
}

char*			argReadAccess(char *a)
{
	static char *arg = NULL;
	if (a != NULL)
		arg = a;
	return arg;
}

char*			buffReadAccess(char *a, size_t l)
{
	static char *arg = NULL;
	static size_t length = 0;

	if (a != NULL)
	{
		arg = a;
		length = l;
		return 0;
	}
	if (!l)
		return arg;
	return arg+length;
}

size_t			readFromBuff(char *buffer, size_t maxSize)
{
	char *arg;
	char *endarg;
	size_t size;

	size = 0;
	arg = buffReadAccess(NULL, 0);
	endarg = buffReadAccess(NULL, 1);
	while (size < maxSize && arg < endarg)
	{
		buffer[size] = *arg;
		size++;
		arg++;
	}
	buffReadAccess(arg, endarg - arg);
	return size;
}

size_t			readFromFd(char *buffer, size_t maxSize)
{
	int		size;
	int		fd;
	size_t length;

	fd = fdReadAccess(NULL);

	ft_bzero(buffer, maxSize);
	size = 1;
	length = 0;
	while(length < maxSize && size > 0)
	{
		size = (int)read(fd, &buffer[length], (maxSize-length));
		length += size;
	}
	//ft_printf("BUFF : %s\n", buffer);
	if (size == -1)
		basicError("error while reading from file descriptor");
	return length;
}

size_t			readFromArg(char *buffer, size_t maxSize)
{
	char *arg;
	size_t size;

	size = 0;
	arg = argReadAccess(NULL);
	while (size < maxSize && arg[size])
	{
		buffer[size] = arg[size];
		size++;
	}
	argReadAccess(&arg[size]);
	buffer[size] = 0;
	return size;
}

size_t		readNoWhiteSpace(size_t (reader)(char*, size_t), char *buffer, size_t maxSize)
{
	char whitespaces[] = " \t\n\r";
	char *found;
	size_t length;
	size_t size;
	size_t skip;

	size = reader(buffer, maxSize);
	length = size;
	while (ft_firstOf(buffer, whitespaces, length))
	{
		skip = 0;
		while ((found = ft_firstOf(buffer, whitespaces, length-skip)) != NULL)
		{
			if (found < (buffer+length-1))
				ft_memmove(found, found+1, (buffer+length)-(found+1));
			skip++;
		}
		length -= skip;
		if (size == maxSize)
		{
			maxSize = maxSize-size+skip;
			size = reader(buffer+length, maxSize);
			length += size;
		}
	}
	return length;
}

size_t readFromArg64(char *buff, size_t length)
{
	char buff64[1001];

	if (length >= 1001)
		basicError("can not read more than 1000 bytes from base64 string");
	return readBase64(readFromArg, buff, buff64, length);
}

size_t		readBase64(size_t (reader)(char*, size_t), char *buffer, char *buffer64, size_t maxSize)
{
	static char memory[3] = {0};
	static size_t extra = 0;
	size_t length;
	size_t realLength;

	char *dbg;

//	if (extra > 0)
//		ft_printf("memory before : '%.*s'\n", extra, memory);
	length = 0;
	dbg = buffer;
	while (extra > 0 && maxSize > 0)
	{
//		ft_printf("restore from memory : [%c]\n", memory[0]);
		*buffer = memory[0];
		buffer++;
		ft_memmove(memory, memory+1, 2);
		extra--;
		length++;
		maxSize--;
	}
	if (maxSize == 0)
		return length;
//	ft_printf("first A : [%c]\n", dbg[0]);
	realLength = readNoWhiteSpace(reader, buffer64, divCeil(maxSize, 3) * 4);
//	ft_printf("first B : [%c]\n", dbg[0]);
//	ft_printf("number char read : %zu\n", realLength);
	realLength = base64decode(buffer64, realLength, buffer64);
//	ft_printf("first C : [%c]\n", dbg[0]);
//	ft_printf("buff64 : '%.*s'\n", realLength, buffer64);
//	ft_printf("number char decode : %zu\n", realLength);
	extra = realLength > maxSize ? realLength - maxSize : 0;
//	ft_printf("extra : %zu\n", extra);
//	ft_printf("max to read : %zu\n", maxSize);
	ft_memcpy(buffer, buffer64, realLength-extra);
	ft_memcpy(memory, buffer64 + maxSize, extra);
//	if (extra > 0)
//		ft_printf("memory after : '%.*s'\n", extra, memory);
	return length + realLength - extra;
}
