#include "md5.h"
#include "command.h"

static void update(unsigned int *state, unsigned int* word)
{
	unsigned int r[64] = {OPERATIONS_TABLE};
	unsigned int k[64] = {ELEMENTS_TABLE};
	unsigned int i;
	unsigned int tmp[7];

	tmp[0] = state[0];
	tmp[1] = state[1];
	tmp[2] = state[2];
	tmp[3] = state[3];
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
		{
			tmp[4] = (tmp[1] & tmp[2]) | (~tmp[1] & tmp[3]);
			tmp[5] = i;
		}
		else if (i <= 31)
		{
			tmp[4] = (tmp[3] & tmp[1]) | (~tmp[3] & tmp[2]);
			tmp[5] = (5*i+1)%16;
		}
		else if (i <= 47)
		{
			tmp[4] = tmp[1] ^ tmp[2] ^ tmp[3];
			tmp[5] = (3*i+5)%16;
		}
		else
		{
			tmp[4] = tmp[2] ^ (tmp[1] | ~tmp[3]);
			tmp[5] = (7*i)%16;
		}
		tmp[6] = tmp[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = leftrotate((tmp[0] + tmp[4] + k[i] + word[tmp[5]]), r[i]) + tmp[1];
		tmp[0] = tmp[6];
		//ft_printf("%d : %u %u %u %u\n", i, tmp[0], tmp[1], tmp[2], tmp[3]);
		i++;
	}
	state[0] += tmp[0];
	state[1] += tmp[1];
	state[2] += tmp[2];
	state[3] += tmp[3];
}

void md5(char *string, unsigned int *state, unsigned long int *size, size_t length)
{
	int nblock;
	int i;

	*size = *size + length;
//	ft_printf("\t#R[process one block]#E\n%s\n\n", string);
	nblock = 1;
	if (length < 64)
	{
		string = pad(string, *size, &nblock, length);
//		ft_printf("\t#C[size %llu]#E\n", *size);
	}
	i = 0;
	while (i < nblock)
	{
//		if (length < 64) {
//			ft_printf("length : %zu\n", length);
//			ft_printf("\n#G");
//			for (unsigned int j = 0; j < 64; j+=4) {
//				ft_printf("%u : %u\n", j, *((unsigned int*)&string[i*64+j]));
//			}
//			ft_printf("#E");
//		}
		update(state, (unsigned int*)&string[i*64]);
		i++;
	}
	if (length < 64)
		ft_memdel((void**)&string);
}

char*	md5ToStr(unsigned int *state)
{
	int i = 0;
	char *bytes;

	while (i < 4)
	{
		bytes = (char*)&state[i];
		reverseEndian(bytes, 4);
		i++;
	}
	return ft_strf("%08x%08x%08x%08x", state[0], state[1], state[2], state[3]);
}

static void printResult(unsigned int *state, char* string, char* file, t_digest *cmd)
{
	char* str;

	str = md5ToStr(state);

	if (cmd->quiet)
		ft_printf("%s\n", str);
	else if (cmd->reverse)
		rprintHash(str, string, file, "MD5");
	else
		printHash(str, string, file, "MD5");
	ft_strdel(&str);
	ft_memdel((void**)&state);
}

static unsigned int* initState()
{
	unsigned int init[4] = {INIT_STATE};
	unsigned int *state;
	size_t size;

	size = sizeof(unsigned int) * 4;
	state = ft_memalloc(size);
	ft_memcpy(state, init, size);
	return state;
}

void executeMD5(struct s_command *command)
{
	executeDigest(command, md5, initState, printResult);
}

unsigned int*	hashMD5(char *str)
{
	unsigned int *state;

	argReadAccess(str);
	state = hash(readFromArg, md5, initState, 0);
	return state;
}
