/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:35:32 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/22 17:13:18 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_free_resources(t_token_list *list)
{
	free_token_list(list);
}

int	main(
	// int ac
	// , const char **av 
	// , const char **envp
	)
{
	char			*line;
	t_token_list	*tokens_list;

	// if (ac != 1)
	// 	return (-1);
	// printf("program name: %s\n", av[0]);
	// t_env_list	*list = env_list_init_populated(envp);
	// env_list_print(list);
	// env_list_insert(list, NULL);
	// env_list_insert(list, "HELLO_ARG=hello world");
	// env_list_print(list);
	// env_list_delete(list);
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
			t_token_node *current = tokens_list->head;
			while (current)
			{
				printf("TOKEN: %s\n", current->token->value);
				current = current->next;
			}
			printf("REV:\n");
			current = tokens_list->tail;
			while (current)
			{
				printf("TOKEN: %s\n", current->token->value);
				current = current->prev;
			}
			// printf("TOKENS:\n");
			// print_token_list(tokens_list);
			// t_ast_node *ast = primary_parse(tokens_list);
			// printf("AST:\n");
			// print_ast(ast);
			// free_ast(ast);
			free_token_list(tokens_list);
		}
		free(line);
	}
	ft_free_resources(NULL);
	return (0);
}
