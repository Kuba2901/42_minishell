/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:33:00 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 20:45:25 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Executes the appropriate redirection based on the type of the AST node.
 *
 * This function handles different types of redirections by calling the corresponding
 * redirection function based on the type of the AST node provided.
 *
 * @param shell A pointer to the shell structure containing the shell's state.
 * @param node A pointer to the AST node representing the redirection operation.
 *
 * The function supports the following redirection types:
 * - TOKEN_REDIRECT_IN: Calls execute_redirect_in to handle input redirection.
 * - TOKEN_REDIRECT_OUT: Calls execute_redirect_out to handle output redirection.
 * - TOKEN_APPEND: Calls execute_redirect_append to handle output redirection in append mode.
 */
void	_execute_redirect(t_shell *shell, t_ast_node *node)
{
	if (node->type == TOKEN_REDIRECT_IN)
		execute_redirect_in(shell, node);
	else if (node->type == TOKEN_REDIRECT_OUT)
		execute_redirect_out(shell, node);
	else if (node->type == TOKEN_APPEND)
		execute_redirect_append(shell, node);
}

/**
 * @brief Executes the abstract syntax tree (AST) node.
 *
 * This function takes a shell context and an AST node, and executes the node
 * based on its type. The function handles different types of nodes such as
 * command nodes, pipe nodes, and various types of redirection nodes.
 *
 * @param shell A pointer to the shell context.
 * @param node A pointer to the AST node to be executed.
 *
 * @note If the node is NULL, the function returns immediately.
 * @note The function delegates the execution to specific functions based on
 *       the type of the node.
 */
void	execute_ast(t_shell *shell, t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == TOKEN_STRING)
		execute_command_node(shell, node);
	else if (node->type == TOKEN_PIPE)
		execute_pipe(shell, node);
	else if (node->type == TOKEN_REDIRECT_IN \
			|| node->type == TOKEN_REDIRECT_OUT \
			|| node->type == TOKEN_APPEND || node->type == TOKEN_HEREDOC)
		_execute_redirect(shell, node);
}
