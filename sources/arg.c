#include "arg.h"

t_sslarg	*newArg(int argc, char* argv[], t_list *o, char *c)
{
	t_sslarg *arg;

	arg = ft_memalloc(sizeof(t_sslarg));
	arg->argc = argc;
	arg->argv = argv;
	arg->options = o;
	arg->command = c;
	return arg;
}

void	printArg(t_sslarg *arg)
{
	int i;

	ft_printf_fd(2, "#RCOMMAND = %s#W\n", arg->command);
	ft_printf_fd(2, "#C");
	ft_lstiter(arg->options, printOption);
	ft_printf_fd(2, "#W");
	i = 0;
	while (i < arg->argc)
	{
		ft_printf_fd(2, "#M%s#W\n", arg->argv[i]);
		i++;
	}
}
