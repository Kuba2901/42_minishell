/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:35:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:31:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Executes a complex command in the shell.
 *
 * This function handles the execution of a complex command by expanding environment
 * variables in the command arguments, finding the executable path, and then using
 * execve to execute the command with the serialized environment.
 *
 * @param shell A pointer to the shell structure containing the environment and other shell-related data.
 * @param node A pointer to the AST node representing the command to be executed.
 *
 * The function performs the following steps:
 * 1. Iterates over the command arguments and expands any environment variables.
 * 2. Finds the executable path for the command.
 * 3. If the executable is not found, prints an error message and exits with status 127.
 * 4. Serializes the shell environment.
 * 5. Executes the command using execve with the found executable path, command arguments, and serialized environment.
 *
 * Note: The function does not return as execve replaces the current process image with a new process image.
 */
static void	_execute_complex_command(t_shell *shell, t_ast_node *node)
{
	int		i;
	char	*temp;
	char	*command_path;
	char	**serialized_env;

	i = -1;
	while (node->token_node->args[++i])
	{
		temp = env_value_expand(shell, node->token_node->args[i]);
		free(node->token_node->args[i]);
		node->token_node->args[i] = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	command_path = execute_find_executable(node->token_node->args[0], shell);
	if (!command_path)
	{
		ft_puterror("minishell: `", node->token_node->args[0],
			": command not found");
		exit(127);
	}
	serialized_env = environment_serialize(shell);
	execve(command_path, node->token_node->args, serialized_env);
	free(serialized_env);
}

/**
 * @brief Checks if the first argument of the token node is a private set command.
 *
 * This function determines if the first argument of the token node is a private set command.
 * A private set command is identified by the first character being '=' or if the first argument
 * contains an '=' character and there is a second argument present.
 *
 * @param node A pointer to the AST node containing the token node with arguments.
 * @return t_bool Returns false if the first argument starts with '=' and reassigns the first argument.
 *                Returns true if the first argument contains '=' and there is a second argument.
 *                Otherwise, returns false.
 */
static t_bool	_is_set_private(t_ast_node *node)
{
	if (node->token_node->args[0][0] == '=')
	{
		node->token_node->args[0] = ft_join_reassign(node->token_node->args[0],
				node->token_node->args[1]);
		node->token_node->args[1] = NULL;
		return (false);
	}
	if (ft_strchr(node->token_node->args[0], '=') \
			&& node->token_node->args[1] != NULL)
		return (true);
	return (false);
}

/**
 * @brief Checks if the given AST node represents a built-in command.
 *
 * This function compares the first argument of the token node in the AST node
 * with a list of known built-in commands. If the command matches any of the
 * built-in commands, the function returns true. Additionally, it checks if the
 * command is a private set command using the _is_set_private function.
 *
 * @param node A pointer to the AST node to check.
 * @return true if the command is a built-in command, false otherwise.
 */
static t_bool	_is_builtin(t_ast_node *node)
{
	if (!ft_strcmp(node->token_node->args[0], "pwd"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "env"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "unset"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "export"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "exit"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "echo"))
		return (true);
	if (!ft_strcmp(node->token_node->args[0], "cd"))
		return (true);
	if (_is_set_private(node))
		return (true);
	return (false);
}

/**
 * @brief Executes a built-in shell command based on the provided AST node.
 *
 * This function checks the command in the AST node and calls the corresponding
 * built-in function to execute it. Supported built-in commands include:
 * - pwd: Prints the current working directory.
 * - env: Prints the environment variables.
 * - unset: Unsets an environment variable.
 * - export: Sets an environment variable.
 * - exit: Exits the shell with a status code of 0.
 * - echo: Prints the provided arguments to the standard output.
 * - cd: Changes the current working directory.
 * - set: Sets a private variable (if applicable).
 *
 * @param shell A pointer to the shell structure containing the shell state.
 * @param node A pointer to the AST node containing the command to execute.
 */
static void	_execute_builtin(t_shell *shell, t_ast_node *node)
{
	if (!ft_strcmp(node->token_node->args[0], "pwd"))
		execute_builtin_pwd(shell);
	else if (!ft_strcmp(node->token_node->args[0], "env"))
		builtin_env(shell);
	else if (!ft_strcmp(node->token_node->args[0], "unset"))
		builtin_unset(shell, node);
	else if (!ft_strcmp(node->token_node->args[0], "export"))
		builtin_export(shell, node);
	else if (!ft_strcmp(node->token_node->args[0], "exit"))
		shell->exit_code = 0;
	else if (!ft_strcmp(node->token_node->args[0], "echo"))
		builtin_echo(shell, node);
	else if (!ft_strcmp(node->token_node->args[0], "cd"))
		builtin_cd(shell, node->token_node->args);
	else if (_is_set_private(node))
		builtin_set_private(shell, node);
	return ;
}

/**
 * @brief Executes a command node in the shell's abstract syntax tree (AST).
 *
 * This function determines if the command node represents a built-in command
 * or a more complex command. If it is a built-in command, it executes it
 * directly. Otherwise, it forks a new process to execute the complex command.
 *
 * @param shell A pointer to the shell structure containing the shell's state.
 * @param node A pointer to the AST node representing the command to be executed.
 *
 * @note If the command is not a built-in, the function forks a new process.
 *       The parent process waits for the child process to complete and updates
 *       the shell's exit code based on the child's exit status.
 */
void	execute_command_node(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
	int		status;

	if (_is_builtin(node))
	{
		_execute_builtin(shell, node);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(errno);
	}
	if (pid == 0)
		_execute_complex_command(shell, node);
	else
	{
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
}
