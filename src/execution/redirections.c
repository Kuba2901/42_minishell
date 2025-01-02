#include <execution.h>

void	execute_redirect_in(t_ast_node *node, t_mini *shell)
{
	int		fd;
	int		status;
	pid_t	pid;
	char	*cmd_path;

	cmd_path = find_executable(node->token_node->token->value, shell->env_list);
	if (!cmd_path)
		return ;
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