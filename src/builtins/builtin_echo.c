/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:54:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:16:23 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Determines the index of the first argument that is not an option.
 *
 * This function iterates over the arguments of the `echo` command to identify
 * whether they contain only `-n` options (which suppress the trailing newline).
 * The function stops at the first argument that does not match this pattern.
 *
 * @param node The AST node containing the command and its arguments.
 * @return The index of the first non-option argument.
 */
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

/**
 * @brief Implements the `echo` built-in command for the minishell.
 *
 * This function mimics the behavior of the UNIX `echo` command, supporting
 * the `-n` option to suppress the trailing newline. It expands environment
 * variables within arguments and prints the result to standard output.
 *
 * @param shell The shell structure containing environment variables and state.
 * @param node The AST node representing the `echo` command and its arguments.
 */
void	builtin_echo(t_shell *shell, t_ast_node *node)
{
	char	**args;
	char	*arg;
	size_t	first_arg;
	t_bool	display_newline;

	args = node->token_node->args;
	first_arg = _determine_first_arg(node) - 1;
	if (first_arg == 0)
		display_newline = true;
	else
		display_newline = false;
	while (args[++first_arg])
	{
		arg = env_value_expand(shell, args[first_arg]);
		if (!arg)
			continue ;
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
