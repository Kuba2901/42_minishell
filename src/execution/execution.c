/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:17 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/29 12:06:33 by jnenczak         ###   ########.fr       */
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

void	execute_command_node(t_ast_node *node, t_mini *shell) {
    pid_t	pid;
	char	*cmd_path;
	
	cmd_path = find_executable(node->token_node->token->value, shell->env_list);
	if (!cmd_path) return;
	pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        if (shell->in_fd != STDIN_FILENO) {
            dup2(shell->in_fd, STDIN_FILENO);
            close(shell->in_fd);
        }
        if (shell->out_fd != STDOUT_FILENO) {
            dup2(shell->out_fd, STDOUT_FILENO);
            close(shell->out_fd);
        }
        // execve(cmd_path, node->token_node, shell->env);
        perror("execve"); // Only reached if execve fails
        exit(EXIT_FAILURE);
    } else { // Parent process
    //     // Optionally save the PID for later management
    //     shell->pids[node->index] = pid;

    //     // Wait for the child to finish, if required
    //     if (!node->is_background) {
    //         int status;
    //         waitpid(pid, &status, 0);
    //         shell->last_exit_status = WEXITSTATUS(status);
    //     }
    }
}

