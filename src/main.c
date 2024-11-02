#include <minishell.h>

int	main(void)
{
	char	*line;
	char	**sentences;

	while (true)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (!ft_is_whitespace(line))
		{
			sentences = ft_split_sentences(line);
			ft_print_enhanced_split(sentences);
			free(sentences);
		}
		free(line);
	}
	return (0);
}