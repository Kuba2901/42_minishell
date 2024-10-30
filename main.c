#include <minishell.h>

int	main(int ac, const char **av)
{
	if (ac != 2) 
		return (0);
	const char *str = av[1];
	const char *charset = " |&<>";
	char **s = ft_enhanced_split(str, charset);
	printf("Counted tokens: %zu\n", ft_count_tokens(str));
	ft_print_enhanced_split(s);
	ft_free_enhanced_split(s);
	return (0);
}