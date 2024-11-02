#include <minishell.h>

int	main(void)
{
	char	*line;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (ft_is_whitespace(line) == false)
			ft_print_enhanced_split(ft_split_sentences(line));
		free(line);
	}
	return (0);
}