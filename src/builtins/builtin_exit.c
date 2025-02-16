/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:11:49 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:22:05 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Counts the number of arguments provided to the exit command.
 *
 * This function iterates through the argument list of the `exit` command
 * to determine how many arguments have been provided.
 *
 * @param node The AST node containing the exit command and its arguments.
 * @return The number of arguments passed to the exit command.
 */
static int	_count_exit_args(t_ast_node *node)
{
	int	count;

	count = 0;
	while (node->token_node->args[count])
		count++;
	return (count);
}

/**
 * @brief Checks the number and validity of arguments for the exit command.
 *
 * This function ensures that the exit command has the correct number of 
 * arguments and that any provided argument is a valid numeric value.
 * If too many arguments are provided, or if a non-numeric argument is given, 
 * an error message is displayed.
 *
 * @param node The AST node containing the exit command and its arguments.
 * @return BUILTIN_EXIT_TOO_MANY_ARGS if too many arguments are given, 
 *         BUILTIN_EXIT_NON_NUMERIC_ARG if an invalid argument is provided, 
 *         or BUILTIN_EXIT_OK if the arguments are valid.
 */
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

/**
 * @brief Handles the execution of the `exit` built-in command.
 *
 * This function checks if the `exit` command is properly formatted and 
 * executes it, freeing necessary resources before terminating the shell.
 * The function ensures:
 * - The command is correctly formatted with a single `exit` keyword.
 * - Argument validity is checked, allowing a numeric exit code.
 * - The shell's exit code is set appropriately.
 * - Memory cleanup is performed before exiting.
 *
 * @param shell A pointer to the shell structure.
 * @param node_ptr A double pointer to the AST node containing the command.
 * @param line_ptr A pointer to the command line input to be freed.
 * @param list_ptr A pointer to the token list to be freed.
 * @return true if the `exit` command was executed, false otherwise.
 */
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
