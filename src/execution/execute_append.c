/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:38:26 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:50:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * execute_redirect_append - Executes a command with output redirected to a 
 * file in append mode.
 * @shell: Pointer to the shell structure containing environment variables 
 * and state.
 * @node: Pointer to the AST node representing the command and redirection.
 *
 * This function performs the following steps:
 * 1. Duplicates the current STDOUT file descriptor to save the original 
 *    STDOUT.
 * 2. Expands the file name using environment variable expansion.
 * 3. Opens the file in append mode, creating it if it does not exist.
 * 4. Redirects STDOUT to the opened file.
 * 5. Executes the command represented by the left child of the AST node.
 * 6. Restores the original STDOUT.
 * 7. Closes the file descriptors.
 *
 * If the file cannot be opened, the function prints an error message and 
 * exits.
 */
void	execute_redirect_append(t_shell *shell, t_ast_node *node)
{
	int		fd;
	int		original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	fd = execution_redirect_open_file(shell, node);
	if (!shell->top_level_redir_out_enabled)
	{
		shell->top_level_redir_out_enabled = true;
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_ast(shell, node->left);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
		shell->top_level_redir_out_enabled = false;
	}
	else
	{
		close(fd);
		execute_ast(shell, node->left);
	}
}
