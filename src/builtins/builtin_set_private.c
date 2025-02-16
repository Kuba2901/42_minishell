/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_private.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:43 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:25:53 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Sets a private environment variable in the shell.
 *
 * This function takes a shell structure and an AST node, and sets a private
 * environment variable based on the arguments provided in the AST node. If the
 * required arguments are not present, it sets the shell's exit code to 1 and
 * returns. Otherwise, it creates a new environment entry and updates the shell's
 * environment.
 *
 * @param shell A pointer to the shell structure.
 * @param node A pointer to the AST node containing the arguments.
 */
void	builtin_set_private(t_shell *shell, t_ast_node *node)
{
	char	*entry;

	if (!node->token_node->args || !node->token_node->args[0] \
			|| !node->token_node->args[1])
	{
		shell->exit_code = 1;
		return ;
	}
	entry = ft_join_reassign(node->token_node->args[0],
			node->token_node->args[1]);
	node->token_node->args[1] = NULL;
	node->token_node->args[0] = entry;
	enviroment_node_create(node->token_node->args[0], shell, true);
	shell->exit_code = 0;
}
