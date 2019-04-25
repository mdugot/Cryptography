#include "option.h"
#include "arg.h"

const char* container[] = {
	"#rsa#rsautl",
	"inform",
	"outform",
	"in",
	"out",
	"passin",
	"passout",
	"inkey",
	"#des#des-ecb#des-cbc",
	"p",
	"#md5#sha256#genrsa#base64",
	"s",
	"i",
	"o",
	"k",
	"v",
	"rand",
	NULL
};

int		isContainer(char *name, char *str)
{
	int i;
	int skip;
	char *ad;

	i = 0;
	skip = 1;
	while (container[i] != NULL)
	{
		ad = ft_strstr(container[i], name);
		if (ad && ad > container[i] && ad[-1] == '#')
			skip = 0;
		if (!skip && ft_strcmp(str, container[i]) == 0)
			return 1;
		i++;
	}
	return 0;
}


t_pair 	*newPair(char *key, char *value)
{
	t_pair *pair;

	pair = ft_memalloc(sizeof(t_pair));
	if (key == NULL)
		pair->key = NULL;
	else
		pair->key = ft_strdup(key);
	if (value == NULL)
		pair->value = NULL;
	else
		pair->value = ft_strdup(value);
	return pair;
}

void	deletePair(t_pair* pair, size_t size)
{
	(void)size;
	if (pair->key != NULL)
		free(pair->key);
	if (pair->value != NULL)
		free(pair->value);
	free(pair);
}

void	printOption(t_list *elem)
{
	t_pair* pair;

	pair = elem->content;
	if (pair->value == NULL)
		ft_printf_fd(2, "%s\n", pair->key);
	else
		ft_printf_fd(2, "%s = %s\n", pair->key, pair->value);
}


void	nextArg(t_sslarg *arg)
{
	arg->argc = arg->argc - 1;
	arg->argv = &arg->argv[1];
}

int 		expectContent(char *name, t_pair *last)
{
	if (last == NULL || last->key == NULL || last->value != NULL) 
		return 0;
	return isContainer(name, last->key);
}

t_pair		*parseOneArg(t_sslarg *arg, t_pair *last, int *end)
{
	ft_printf_fd(2, "parse : %s\n", arg->argv[0]);
	if (arg->command != NULL && expectContent(arg->command, last))
		last->value = arg->argv[0];
	else if (ft_strcmp("--", arg->argv[0]) == 0)
	{
		*end = 1;
		nextArg(arg);
	}
	else if (*end == 0 && arg->argv[0][0] == '-')
	{
		last = newPair(arg->argv[0]+1, NULL);
		ft_lstadd_end(&arg->options, ft_lstnew_noalloc(last, sizeof(t_pair)));
	}
	else
	{
		if (arg->command == NULL)
			arg->command = arg->argv[0];
		else
			*end = 1;
	}
	return last;
}

t_sslarg	*parseOptions(int argc, char *argv[])
{
	t_sslarg	*arg;
	t_pair		*last;
	int			end;

	end = 0;
	arg = newArg(argc, argv, NULL, NULL);
	last = NULL;
	while (arg->argc > 1 && !(arg->command && end)) {
		nextArg(arg);
		last = parseOneArg(arg, last, &end);
	}
	if (end == 0)
		nextArg(arg);
	return arg;
}
