/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:35:32 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/14 17:53:31 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_free_resources(t_token_list *list)
{
	free_token_list(list);
}

int	main(int ac, const char **av, const char **envp)
{
	char			*line;
	t_token_list	*tokens_list;

	if (ac != 1)
		return (-1);
	printf("program name: %s\n", av[0]);
	t_env_list	*list = create_env_list(envp);
	insert_env_node("HOMEBREW_TEST=\"test_node\"", list);
	print_env_list(list);
	insert_env_node("HOMEBREW_TEST=\"changed_test_node\"", list);
	print_env_list(list);
	delete_env_node(list, "HOMEBREW_TEST");
	print_env_list(list);
	delete_env_node(list, "NON_EXISTENT");
	print_env_list(list);
	free_env_list(list);
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
