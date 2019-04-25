#include "command.h"
#include "des.h"
#include "base64.h"
#include "millerRabin.h"
#include "rsa.h"

int		main(int argc, char *argv[]) {
	t_sslarg	*arg;

//	t_rsakey *key = createRsaKey(ft_ssl_is_primary, 0.99);
//	printRsaKey(key);
//	exit(0);
//	__int64_t n = randomInt64(3, 100000);
//	__int64_t n = 914713;
//	ft_printf("random int = %llu\n", n);
//	int prime = ft_ssl_is_primary(n, 0.7);
//	ft_printf("%llu is prime ? %d\n", n, prime);
//	exit(0);

	initAllCommands();
	arg = parseOptions(argc, argv);
	printArg(arg);
	checkCommand(arg);
	executeCommand(arg);

	ft_putendl("");
	return 0;
}
