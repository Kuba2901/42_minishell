/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:11:15 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:24:42 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Handles the export builtin command in the shell.
 *
 * This function processes the export command, which is used to set environment
 * variables. If no arguments are provided, it prints the environment variables
 * in sorted order. If arguments are provided, it attempts to set the specified
 * environment variables.
 *
 * @param shell A pointer to the shell structure containing the environment.
 * @param node A pointer to the AST node representing the export command and its arguments.
 */
void	builtin_export(t_shell *shell, t_ast_node *node)
{
	if (!node || !node->token_node->args)
		return ;
	if (!node->token_node->args[1])
	{
		environment_list_print_sorted(shell);
		return ;
	}
	if (!builtin_export_export_key_value(shell, node))
		shell->exit_code = 0;
	else
		shell->exit_code = 1;
}
