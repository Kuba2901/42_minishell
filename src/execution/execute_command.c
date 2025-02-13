/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:35:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 23:08:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

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
		fprintf(stderr, "minishell: %s: command not found\n",
			node->token_node->args[0]);
		exit(127);
	}
	serialized_env = environment_serialize(shell);
	execve(command_path, node->token_node->args, serialized_env);
	free(serialized_env);
}

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
	if (_is_set_private(node))
		return (true);
	return (false);
}

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
	else if (_is_set_private(node))
		builtin_set_private(shell, node);
	return ;
}

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
