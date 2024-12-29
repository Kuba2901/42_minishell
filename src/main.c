/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:35:32 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/29 11:56:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_free_resources(t_mini *mini)
{
	if (mini == NULL)
		return ;
	env_list_delete(mini->env_list);
}

int	main(int ac, const char **av, const char **envp)
{
	char			*line;
	t_token_list	*tokens_list;
	t_mini			mini;

	if (ac != 1)
		return (-1);
	(void)av;
	mini.env_list = env_list_init_populated(envp);
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
			mini.head = primary_parse(tokens_list);
			if (mini.head)
			{
				print_ast(mini.head);
				free_ast(mini.head);
			}
			mini.head = NULL;
			free_token_list(tokens_list);
			tokens_list = NULL;
		}
		free(line);
	}
	char *cmd_path = find_executable("ls -la", mini.env_list);
	if (cmd_path)
	{
		printf("Executable found: %s\n", cmd_path);
		free(cmd_path);
	}
	ft_free_resources(&mini);
	return (0);
}
