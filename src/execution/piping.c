#include <execution.h>

void execute_pipe(t_ast_node *node, t_mini *shell)
{
    int		pipe_fd[2];
    pid_t	pid_left;
	pid_t	pid_right;
    int		status;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return;
    }
    pid_left = fork();
    if (pid_left == -1)
    {
        perror("fork");
        return;
    }
    if (pid_left == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
		execute_ast(node->left, shell);
        _exit(shell->last_exit_status);
    }
    pid_right = fork();
    if (pid_right == -1)
    {
        perror("fork");
        return;
    }
    if (pid_right == 0)
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
		execute_ast(node->right, shell);
        _exit(shell->last_exit_status);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
    shell->last_exit_status = WEXITSTATUS(status);
}
