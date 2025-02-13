/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:11:15 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 20:53:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

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
