/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect_out.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:59 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 16:14:50 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Executes a command with output redirected to a file.
 *
 * This function handles the redirection of the 
 * standard output (stdout) to a file
 * specified in the abstract syntax tree (AST) node. 
 * It first duplicates the current
 * stdout file descriptor to restore it later. 
 * Then, it expands the file name using
 * environment variable expansion, opens 
 * the file with write permissions, and redirects
 * stdout to this file. After executing the 
 * command represented by the left child of
 * the AST node, it restores the original stdout file descriptor.
 *
 * @param shell Pointer to the shell structure 
 * containing the environment and state.
 * @param node Pointer to the AST node representing 
 * the redirection operation.
 */
void	execute_redirect_out(t_shell *shell, t_ast_node *node)
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
