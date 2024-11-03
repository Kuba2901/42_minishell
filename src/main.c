/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:35:32 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 18:28:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			if (ft_strncmp(line, "exit", 4) == 0)
				break ;
			tokens_list = ft_tokenize(line);
			printf("TOKENS:\n");
			print_token_list(tokens_list);
			t_ast_node *ast = primary_parse(tokens_list);
			printf("AST:\n");
			print_ast(ast);
			free_ast(ast);
			free_token_list(tokens_list);
		}
		free(line);
	}
	ft_free_resources(NULL);
	return (0);
}
