/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_private.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:43 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 15:37:08 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

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
