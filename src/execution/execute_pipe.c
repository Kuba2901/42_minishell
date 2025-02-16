/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:34:33 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:33:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Executes the left side of a pipe in a shell.
 *
 * This function is responsible for executing the left side of a pipe in a shell
 * environment. It closes the read end of the pipe, duplicates the write end of
 * the pipe to the standard output file descriptor, and then closes the write
 * end of the pipe. After setting up the pipe, it executes the abstract syntax
 * tree (AST) node on the left side of the pipe and exits with the shell's exit
 * code.
 *
 * @param shell Pointer to the shell structure containing the shell state.
 * @param node Pointer to the AST node representing the left side of the pipe.
 * @param pipe_fd Array of two integers representing the file descriptors for
 * the pipe. pipe_fd[0] is the read end, and pipe_fd[1] is the write end.
 */
static void	execute_pipe_left(t_shell *shell, t_ast_node *node, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_ast(shell, node->left);
	_exit(shell->exit_code);
}

/**
 * @brief Executes the right side of a pipe in a shell.
 *
 * This function is responsible for executing the right side of a pipe
 * command in the shell. It closes the write end of the pipe, duplicates
 * the read end of the pipe to the standard input, and then closes the
 * read end of the pipe. Finally, it executes the abstract syntax tree
 * (AST) node on the right side of the pipe and exits with the shell's
 * exit code.
 *
 * @param shell Pointer to the shell structure containing the shell state.
 * @param node Pointer to the AST node representing the right side of the pipe.
 * @param pipe_fd Array containing the file descriptors for the pipe.
 */
static void	execute_pipe_right(t_shell *shell, t_ast_node *node, int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_ast(shell, node->right);
	_exit(shell->exit_code);
}

/**
 * @brief Executes a command pipeline by forking two child processes.
 *
 * This function creates a pipe and forks two child processes to execute
 * the left and right sides of a pipeline. The left child process writes
 * to the pipe, and the right child process reads from the pipe. The parent
 * process waits for both child processes to complete and sets the shell's
 * exit code based on the status of the right child process.
 *
 * @param shell A pointer to the shell structure.
 * @param node A pointer to the abstract syntax tree node representing the pipeline.
 */
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
