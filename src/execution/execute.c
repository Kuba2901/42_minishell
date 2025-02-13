/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:33:00 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:43:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

void	_execute_redirect(t_shell *shell, t_ast_node *node)
{
	if (node->type == TOKEN_REDIRECT_IN)
		execute_redirect_in(shell, node);
	else if (node->type == TOKEN_REDIRECT_OUT)
		execute_redirect_out(shell, node);
	else if (node->type == TOKEN_APPEND)
		execute_redirect_append(shell, node);
}

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
