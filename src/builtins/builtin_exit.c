/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:11:49 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:08:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

static int	_count_exit_args(t_ast_node *node)
{
	int	count;

	count = 0;
	while (node->token_node->args[count])
		count++;
	return (count);
}

static int	_check_arg_num(t_ast_node *node)
{
	int	count;

	count = _count_exit_args(node);
	if (count > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (BUILTIN_EXIT_TOO_MANY_ARGS);
	}
	if (node->token_node->args[1])
	{
		if (!ft_isdigit(node->token_node->args[1][0]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(node->token_node->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (BUILTIN_EXIT_NON_NUMERIC_ARG);
		}
	}
	return (BUILTIN_EXIT_OK);
}

t_bool	builtin_exit(t_shell *shell, t_ast_node **node_ptr, char **line_ptr,
			t_token_node ***list_ptr)
{
	t_ast_node		*ast;
	t_token_node	**tokens;
	char			*line;
	int				exit_code;

	ast = *node_ptr;
	tokens = *list_ptr;
	line = *line_ptr;
	if (!(!ast->left && !ast->right \
			&& !ft_strcmp(ast->token_node->args[0], "exit")))
		return (false);
	if (_check_arg_num(ast))
		exit_code = ft_atoi(ast->token_node->args[1]) % 256;
	else
		exit_code = shell->exit_code;
	ast_delete(ast);
	free(tokens);
	free(line);
	shell->exit_code = exit_code;
	return (true);
}
