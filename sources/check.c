#include "check.h"

int hasOption(t_sslarg *arg, char *toCheck)
{
	t_list *tmp;
	t_pair *pair;

	tmp = arg->options;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, toCheck) == 0)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

void allowOptions(t_sslarg *arg, char **options)
{
	t_list *tmp;
	t_pair *pair;
	int	ok;
	int i;

	tmp = arg->options;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		ok = 0;
		i = 0;
		while (options[i])
		{
			if (ft_strcmp(pair->key, options[i]) == 0)
				ok = 1;
			i++;
		}
		if (!ok)
			wrongArg(arg, ft_strf("unknown option '%s'", pair->key));
		tmp = tmp->next;
	}
}

char* findContent(t_sslarg *arg, char *toCheck, int idx)
{
	t_list *tmp;
	t_pair *pair;
	int i;

	tmp = arg->options;
	i = 0;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, toCheck) == 0)
		{
			if (idx == i)
			{
				if (pair->value == NULL)
					wrongArg(arg, ft_strf("must have -%s with value", toCheck));
				return pair->value;
			}
			else
				i++;
		}
		tmp = tmp->next;
	}
	return NULL;
}

char* getContent(t_sslarg *arg, char *toCheck)
{
	char *content;

	if (hasOption(arg, toCheck) == 0)
		return NULL;
	content = findContent(arg, toCheck, 0);
	return content;
}

int countOptions(t_sslarg *arg, char *toCheck)
{
	t_list *tmp;
	t_pair *pair;
	int i;

	tmp = arg->options;
	i = 0;
	while (tmp != NULL)
	{
		pair = (t_pair*)tmp->content;
		if (ft_strcmp(pair->key, toCheck) == 0)
				i++;
		tmp = tmp->next;
	}
	return i;
}

char** getListContents(t_sslarg *arg, char *toCheck)
{
	char **contents;
	int count;
	int i;

	count = countOptions(arg, toCheck);
	if (count <= 0)
		return NULL;
	contents = ft_memalloc((count+1) * sizeof(char*));
	i = 0;
	while (i < count)
	{
		contents[i] = findContent(arg, toCheck, i);
		i++;
	}
	contents[i] = NULL;
	return contents;
}
