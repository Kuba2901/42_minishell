/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:27:34 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:02:11 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

static char	*_search_in_path(char *command, char **directories)
{
	int		i;
	char	*full_path;

	i = -1;
	while (directories[++i])
	{
		full_path = ft_join_reassign(directories[i], ft_strdup("/"));
		full_path = ft_join_reassign(full_path, ft_strdup(command));
		if (access(full_path, X_OK) == 0)
		{
			while (directories[++i])
				free(directories[i]);
			break ;
		}
		free(full_path);
		full_path = NULL;
	}
	free(directories);
	return (full_path);
}

/**
 * @brief Finds the full path of an executable command.
 *
 * This function searches for the given command in the directories specified
 * by the PATH environment variable. If the command is an absolute path or a
 * relative path starting with "./", it checks if the command is executable.
 *
 * @param command The command to find the executable path for.
 * @param shell The shell structure containing environment variables.
 * @return A dynamically allocated string containing the full path of the
 * executable if found, or NULL if the command is not found or not executable.
 */
char	*execute_find_executable(char *command, t_shell *shell)
{
	char	*path_env;
	char	**dir;

	if (!command)
		return (NULL);
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	path_env = environment_list_read("PATH", shell);
	if (!path_env || !ft_strcmp(path_env, ""))
		return (NULL);
	dir = ft_split(path_env, ':');
	return (_search_in_path(command, dir));
}

static int	execution_open_file_type(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_REDIRECT_IN)
		return (O_RDONLY);
	else if (node->type == TOKEN_REDIRECT_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (node->type == TOKEN_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (0);
}

int	execution_redirect_open_file(t_shell *shell, t_ast_node *node)
{
	int		fd;
	char	*expanded_file_name;

	expanded_file_name = env_value_expand(shell,
			node->right->token_node->args[0]);
	fd = open(expanded_file_name, execution_open_file_type(node), 0644);
	free(expanded_file_name);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}
