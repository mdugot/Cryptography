#include "writer.h"


char*			buffWriteAccess(char *a, size_t l)
{
	static char *arg = NULL;
	static size_t limit = 0;

	if (a != NULL)
	{
		arg = a;
		limit = l;
		return 0;
	}
	if (!l)
		return arg;
	return arg+limit;
}

void			writeToBuff(char *buffer, size_t length)
{
	char	*buff;
	char	*endbuff;

	buff = buffWriteAccess(NULL, 0);
	endbuff = buffWriteAccess(NULL, 1);
	if (length >= (size_t)(endbuff - buff))
		basicError("full buffer error");
	ft_memcpy(buff, buffer, length);
	buffWriteAccess(buff+length, endbuff - buff - length);
}

int				fdWriteAccess(char *filename)
{
	static int fd = 1;
	if (filename != NULL)
	{
		if (fd != 1)
			close(fd);
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			wrongFile(filename, "can not open file");
	}
	return fd;
}

void			writeToFd(char *buffer, size_t length)
{
	int		fd;
	int		result;

	fd = fdWriteAccess(NULL);

	result = (int)write(fd, buffer, length);
	if (result == -1)
		basicError("error while writing to file descriptor");
}

void			writeToFd64(char *buffer, size_t length)
{
		char str64[4004] = {0};

		if (length >= 3000)
			basicError("can not write more than 3000 bytes in base64");
		base64encode(buffer, length, str64);
		writeToFd_64line(str64, ft_strlen(str64));
}

void			writeToFd_64line(char *buffer, size_t length)
{
	static int counter = 0;

	while (length > 0)
	{
		if (counter + length <= 64)
		{
			counter += length;
			writeToFd(buffer, length);
			length = 0;
		}
		else
		{
			writeToFd(buffer, 64 - counter);
			buffer += 64 - counter;
			length -= 64 - counter;
			counter = 0;
			writeToFd("\n", 1);
		}
	}
}
