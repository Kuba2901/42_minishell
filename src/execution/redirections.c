#include <execution.h>

void execute_redirect_in(t_ast_node *node, t_mini *shell)
{
	int	original_stdin;
	int	fd;

    original_stdin = dup(STDIN_FILENO);  // Save the original stdin
    fd = open(node->right->token_node->token->value, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    execute_command_node(node->left, shell, false);
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
}

void	execute_redirect_out(t_ast_node *node, t_mini *shell)
{
	int		fd;
	int		original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	fd = open(node->right->token_node->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_ast(node->left, shell);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	execute_redirect_append(t_ast_node *node, t_mini *shell)
{
	int		fd;
	int		original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	fd = open(node->right->token_node->token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_ast(node->left, shell);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}