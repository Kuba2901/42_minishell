/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:33:34 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:50:50 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Executes a command with input redirection.
 *
 * This function handles the execution of a command where the input is 
 * redirected from a file. It temporarily replaces the standard input (stdin) 
 * with the contents of the specified file, executes the command, and then 
 * restores the original stdin.
 *
 * @param shell Pointer to the shell structure containing environment and 
 * state information.
 * @param node Pointer to the AST node representing the command and its 
 * redirection.
 *
 * The function performs the following steps:
 * 1. Duplicates the current stdin file descriptor to save it.
 * 2. Expands the file name using environment variable expansion.
 * 3. Opens the file for reading.
 * 4. If the file cannot be opened, prints an error message and exits.
 * 5. Redirects stdin to the opened file.
 * 6. Executes the command represented by the left child of the AST node.
 * 7. Restores the original stdin.
 * 8. Closes the duplicated stdin file descriptor.
 */
void	execute_redirect_in(t_shell *shell, t_ast_node *node)
{
	int		original_stdin;
	int		fd;

	original_stdin = dup(STDIN_FILENO);
	fd = execution_redirect_open_file(shell, node);
	if (!shell->top_level_redir_in_enabled)
	{
		shell->top_level_redir_in_enabled = true;
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_ast(shell, node->left);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		shell->top_level_redir_in_enabled = false;
	}
	else
	{
		close(fd);
		execute_ast(shell, node->left);
	}
}
