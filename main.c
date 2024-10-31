#include <minishell.h>

int	main(int ac, const char **av)
{
	if (ac != 2) 
		return (0);
	printf("Hello world!\n");
	printf("%s\n", av[1]);
	return (0);
}