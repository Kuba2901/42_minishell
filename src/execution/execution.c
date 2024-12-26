/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:17 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/15 17:45:59 by jnenczak         ###   ########.fr       */
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

void	execute_command(t_ast_node *node, t_env_list *env_list)
{
	char	*cmd_path;
	char	**argv;
	int		i;

	if (node->type != AST_COMMAND)
		return ;
	cmd_path = find_executable(node->token_node->token->value, env_list);
	if (!cmd_path)
	{
		printf("Command not found: %s\n", node->token_node->token->value);
		return ;
	}
	size_t	args_count = 0;
	while (node->token_node->token->args[args_count])
		args_count++;
	argv = malloc(sizeof(char *) * (args_count + 2));
	argv[0] = ft_strdup(node->token_node->token->value);
	i = -1;
	while (node->token_node->token->args[++i])
		argv[i + 1] = ft_strdup(node->token_node->token->args[i]);
	argv[i + 1] = NULL;
	execve(cmd_path, argv, NULL);
	perror("execve");
	free(cmd_path);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}