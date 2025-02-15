/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:54:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 16:07:50 by jnenczak         ###   ########.fr       */
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
	first_arg = _determine_first_arg(node) - 1;
	if (first_arg == 0)
		display_newline = true;
	else
		display_newline = false;
	while (args[++first_arg])
	{
		arg = env_value_expand(shell, args[first_arg]);
		printf("%s", arg);
		if (args[first_arg + 1] && args[first_arg]
			[ft_strlen(args[first_arg]) - 1] != '=')
			printf(" ");
		free(arg);
	}
	if (display_newline)
		printf("\n");
	shell->exit_code = 0;
}
