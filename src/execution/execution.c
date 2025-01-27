/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:17 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/29 12:11:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

char	*find_executable(const char *command, t_env_list *env_list)
{
	char	*path_env;
	char	**dir;
	char	*full_path;
	int		i;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}

	path_env = env_value_read(env_list, "PATH");
	if (!path_env) return (NULL);
	dir =  ft_split(path_env, ':');
	i = -1;
	while (dir[++i])
	{
		full_path = ft_strdup(dir[i]);
		full_path = ft_join_reassign(dir[i], ft_strdup("/"));
		full_path = ft_join_reassign(full_path, ft_strdup(command));
		if (access(full_path, X_OK) == 0) {
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
	}
	free(dir);
	path_env = NULL;
	dir = NULL;
	return (NULL);
}

static void	_execute_complex_command(t_mini *shell, char *cmd_path, char **args)
{
	int		i;
	char	**cmd_args;
	char	*expanded_value;

	i = -1;
	while (args[++i])
		;
	cmd_args = malloc(sizeof(char *) * (i + 2));
	if (!cmd_args) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd_args[0] = cmd_path;
	if (args != NULL) {
		i = -1;
		while (args[++i])
		{
			if (args[i][0] == '$')
			{
				expanded_value = env_value_read(shell->env_list, args[i] + 1);
				free(args[i]);
				if (expanded_value == NULL)
					args[i] = ft_strdup("");
				else
					args[i] = expanded_value;
				cmd_args[i + 1] = args[i];
			}
			else
				cmd_args[i + 1] = args[i];
		}
	}
	cmd_args[i + 1] = NULL;
	execve(cmd_path, cmd_args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	_execute_child_process(t_mini *shell, char *cmd_path, t_ast_node *node)
{
	_execute_complex_command(shell, cmd_path, node->token_node->token->args);	
}

void	execute_command_node(t_ast_node *node, t_mini *shell, t_bool is_another_process)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_executable(node->token_node->token->value, 
		shell->env_list);
	if (!is_another_process)
		_execute_child_process(shell, cmd_path, node);
	else
	{
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) {
			_execute_child_process(shell, cmd_path, node);
		}
		else {
			waitpid(pid, &status, 0);
			shell->last_exit_status = WEXITSTATUS(status);
		}
	}
}

void	_execute_redirect(t_ast_node *node, t_mini *shell)
{
	if (node->type == AST_REDIRECT_IN)
		execute_redirect_in(node, shell);
	else if (node->type == AST_REDIRECT_OUT)
		execute_redirect_out(node, shell);
	else if (node->type == AST_APPEND)
		execute_redirect_append(node, shell);
	// TODO: RETURN TO THE MINISHEEL INTERFACE FOR INPUT
}


void	execute_ast(t_ast_node *node, t_mini *shell)
{
	if (!node)
		return;
	if (node->type == AST_COMMAND)
		execute_command_node(node, shell, true);
	else if (node->type == AST_PIPE)
		execute_pipe(node, shell);
	else if (node->type == AST_REDIRECT_IN || node->type == AST_REDIRECT_OUT || node->type == AST_APPEND)
		_execute_redirect(node, shell);
	// Add support for other types of nodes
}