#include <minishell.h>

int	main(int ac, const char **av)
{
	if (ac != 2) 
		return (0);
	char **split = ft_split_sentences(av[1]);
	ft_print_enhanced_split(split);
	ft_free_enhanced_split(split);
	return (0);
}