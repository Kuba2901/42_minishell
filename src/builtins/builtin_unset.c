/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:05:37 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/16 21:26:13 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Unsets environment variables in the shell.
 *
 * This function removes environment variables specified in the arguments
 * from the shell's environment. If no arguments are provided, it prints
 * an error message indicating that not enough arguments were given.
 *
 * @param shell A pointer to the shell structure.
 * @param node A pointer to the AST node containing the command and its arguments.
 */
void	builtin_unset(t_shell *shell, t_ast_node *node)
{
	int					i;
	char				**args;

	args = node->token_node->args;
	if (args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = 0;
	while (args[++i] != NULL)
		enviroment_node_delete(args[i], shell);
	printf("\n");
	shell->exit_code = 0;
}
