/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:10 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 21:46:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	_clear_screen_ensure_cursor_visible(void)
{
	printf("\033[2J\033[H");
}

static void	_free_resources(t_shell *shell)
{
	environment_list_clear(shell);
	_clear_screen_ensure_cursor_visible();
}

void	_init_shell(t_shell *shell, const char **envp)
{
	shell->env = NULL;
	shell->exit_code = 0;
	shell->env = environment_list_initialize(envp);
	shell->envp = envp;
	shell->top_level_redir_out_enabled = false;
	shell->top_level_redir_in_enabled = false;
	if (!shell->env)
	{
		perror("Failed to initialize environment list\n");
		exit(EXIT_FAILURE);
	}
}

static void	_handle_input(t_shell *shell)
{
	char			*line;
	t_token_node	**list;
	t_ast_node		*ast;

	(void)shell;
	while (true)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		list = tokenise(line);
		ast = ast_create(list);
		execute_preprocess_heredocs(ast);
		if (!ast->left && !ast->right && !ft_strcmp(ast->token_node->args[0],
				"exit"))
		{
			builtin_exit(shell, &ast, &line, &list);
			break ;
		}
		execute_ast(shell, ast);
		ast_delete(ast);
		free(list);
		add_history(line);
		free(line);
	}
}

int	main(int ac, const char **av, const char **envp)
{
	t_shell	shell;
	int		exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	if (ac == 2 && !ft_strcmp(av[1], "--full"))
		show_intro();
	_init_shell(&shell, envp);
	signals_setup();
	_handle_input(&shell);
	exit_code = shell.exit_code;
	_free_resources(&shell);
	return (exit_code);
}
