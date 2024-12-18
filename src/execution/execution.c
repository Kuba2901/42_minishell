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

char	*find_executable(const char *command)
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

	path_env = getenv("PATH");
	if (!path_env) return (NULL);
	dir =  ft_split(path_env, ':');
	i = -1;
	while (dir[++i])
	{
		full_path = ft_strdup(dir[i]);
		full_path = ft_join_reassign(dir[i], "/");
		full_path = ft_join_reassign(full_path, (char *)command);
		if (access(full_path, X_OK) == 0) {
			free(path_env);
			return ft_strdup(full_path);
		}
		free(full_path);
		full_path = NULL;
	}
	i = -1;
	while (dir[++i])
		free(dir[i]);
	free(dir);
	free(path_env);
	path_env = NULL;
	dir = NULL;
	return NULL;
}
