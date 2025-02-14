/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:54:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 21:49:09 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

static size_t	_determine_first_arg(t_ast_node *node)
{
	char	**args;
	size_t	i;
	size_t	j;
	char	c;

	args = node->token_node->args;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			c = args[i][j];
			if (c != 'n' && !ft_is_whitespace(c))
				return (i);
		}
		i++;
	}
	return (i);
}

void	builtin_echo(t_shell *shell, t_ast_node *node)
{
	char	**args;
	char	*arg;
	size_t	first_arg;
	t_bool	display_newline;

	args = node->token_node->args;
	if (!args)
		return ;
	first_arg = _determine_first_arg(node);
	if (first_arg == 1)
		display_newline = true;
	else
		display_newline = false;
	while (args[first_arg])
	{
		arg = env_value_expand(shell, args[first_arg]);
		write(STDOUT_FILENO, arg, ft_strlen(arg));
		if (args[first_arg + 1])
			write(STDOUT_FILENO, " ", 1);
		free(arg);
		first_arg++;
	}
	if (display_newline)
		write(STDOUT_FILENO, "\n", 1);
	shell->exit_code = 0;
}
