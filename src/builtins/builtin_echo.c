/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:54:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 23:21:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

void	builtin_echo(t_shell *shell, t_ast_node *node)
{
	t_bool	newline;
	char	**args;
	size_t	i;
	char	*arg;

	args = node->token_node->args;
	newline = true;
	if (args && args[1] && args[1][0] == '-')
	{
		if (args[1][1] == 'n')
			newline = false;
		i = 1;
		while (args[1][++i] && !newline)
		{
			if (args[1][i] != 'n')
				newline = true;
		}
	}
	if (newline)
		i = 0;
	else
		i = 1;
	while (args[++i])
	{
		arg = env_value_expand(shell, args[i]);
		ft_putstr_fd(arg, STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		free(arg);
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	shell->exit_code = 0;
}