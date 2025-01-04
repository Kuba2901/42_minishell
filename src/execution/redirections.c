#include <execution.h>

void	execute_redirect_in(t_ast_node *node, t_mini *shell)
{
	int		fd;
	int		status;
	pid_t	pid;

	printf("execute_redirect_in\n");
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		fd = open(node->right->token_node->token->value, O_RDONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_command_node(node->left, shell);
	}
	else {
		waitpid(pid, &status, 0);
		shell->last_exit_status = WEXITSTATUS(status);
	}
}