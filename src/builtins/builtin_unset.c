/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:05:37 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/12 17:01:18 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

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
