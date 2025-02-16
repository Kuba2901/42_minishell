/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:56:27 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 20:49:18 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <mini_base.h>
#include <minishell.h>

/**
 * @brief Compares two null-terminated strings lexicographically.
 *
 * This function compares the two strings s1 and s2. It returns an integer
 * less than, equal to, or greater than zero if s1 is found, respectively,
 * to be less than, to match, or be greater than s2.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function checks if the given character c is a whitespace character.
 * Whitespace characters include space (' '),
 * horizontal tab ('\t'), newline ('\n'),
 * and carriage return ('\r').
 *
 * @param c The character to be checked.
 * @return A boolean value indicating whether
 * the character is a whitespace character.
 */
t_bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * @brief Writes an error message to the standard error output.
 *
 * This function writes the provided error message and arguments to the standard error output (stderr).
 * If the second argument is NULL, the function returns without writing anything.
 * If the third argument is provided, it will also be written to stderr.
 * A newline character is written at the end of the message.
 *
 * @param s The main error message to be written. Must not be NULL.
 * @param arg1 The first argument to be written. Must not be NULL.
 * @param arg2 The second argument to be written. Can be NULL.
 */
void	ft_puterror(const char *s, char *arg1, const char *arg2)
{
	if (!s || !arg1)
		return ;
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, arg1, ft_strlen(arg1));
	if (arg2)
		write(STDERR_FILENO, arg2, ft_strlen(arg2));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * @brief Clears the terminal screen and ensures the cursor is visible at the top-left corner.
 *
 * This function sends ANSI escape codes to the terminal to clear the screen and move the cursor
 * to the home position (top-left corner). It is useful for refreshing the terminal display.
 */
void	clear_screen_ensure_cursor_visible(void)
{
	printf("\033[2J\033[H");
}

/**
 * @brief Frees resources associated with the shell.
 *
 * This function clears the environment list and ensures the screen is cleared
 * and the cursor is visible.
 *
 * @param shell A pointer to the shell structure containing resources to be freed.
 */
void	free_resources(t_shell *shell)
{
	environment_list_clear(shell);
	clear_screen_ensure_cursor_visible();
}

/**
 * @brief Initializes the shell structure with environment variables and default settings.
 *
 * This function sets up the initial state of the shell by initializing the environment list,
 * setting the exit code to 0, and disabling top-level redirections. If the environment list
 * initialization fails, the function prints an error message and exits the program.
 *
 * @param shell Pointer to the shell structure to be initialized.
 * @param envp  Array of environment variables.
 */
void	init_shell(t_shell *shell, const char **envp)
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

/**
 * @brief Handles the input loop for the shell.
 *
 * This function continuously prompts the user for input, tokenizes the input,
 * creates an abstract syntax tree (AST) from the tokens, preprocesses any
 * heredocs, checks for the exit builtin command, executes the AST, and then
 * cleans up the resources.
 *
 * @param shell A pointer to the shell structure.
 */
void	handle_input(t_shell *shell)
{
	char			*line;
	t_token_node	**list;
	t_ast_node		*ast;

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
		if (builtin_exit(shell, &ast, &line, &list))
			break ;
		execute_ast(shell, ast);
		ast_delete(ast);
		free(list);
		add_history(line);
		free(line);
	}
}