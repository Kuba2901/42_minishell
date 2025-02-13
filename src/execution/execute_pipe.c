/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:34:33 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:33:06 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

static void	execute_pipe_left(t_shell *shell, t_ast_node *node, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_ast(shell, node->left);
	_exit(shell->exit_code);
}

static void	execute_pipe_right(t_shell *shell, t_ast_node *node, int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_ast(shell, node->right);
	_exit(shell->exit_code);
}

void	execute_pipe(t_shell *shell, t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		return ;
	pid_left = fork();
	if (pid_left == -1)
		return ;
	if (pid_left == 0)
		execute_pipe_left(shell, node, pipe_fd);
	pid_right = fork();
	if (pid_right == -1)
		return ;
	if (pid_right == 0)
		execute_pipe_right(shell, node, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
}
