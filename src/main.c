#include <minishell.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void	ft_free_resources(t_token_list *list)
{
	free_token_list(list);
}

int	main(void)
{
	char			*line;
	t_token_list	*tokens_list;

	while (true)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (!ft_is_whitespace(*line))
		{
			tokens_list = ft_tokenize(line);
			print_token_list(tokens_list);
			free_token_list(tokens_list);
		}
		free(line);
	}
	ft_free_resources(NULL); // TODO: Change to real list
	return (0);
}