#include <execution.h>

void execute_redirect_in(t_ast_node *node, t_mini *shell)
{
	int		original_stdin;
	int		fd;
	char	*expanded_file_name;

    original_stdin = dup(STDIN_FILENO);  // Save the original stdin
	if (node->right->token_node->token->value[0] == '$') {
		expanded_file_name = env_value_expand(shell->env_list, node->right->token_node->token->value);
		free(node->right->token_node->token->value);
		if (expanded_file_name == NULL)
			node->right->token_node->token->value = ft_strdup("");
		else
			node->right->token_node->token->value = expanded_file_name;
	}
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
	char	*expanded_file_name;

	original_stdout = dup(STDOUT_FILENO);
	if (node->right->token_node->token->value[0] == '$') {
		expanded_file_name = env_value_expand(shell->env_list, node->right->token_node->token->value);
		free(node->right->token_node->token->value);
		if (expanded_file_name == NULL)
			node->right->token_node->token->value = ft_strdup("");
		else
			node->right->token_node->token->value = expanded_file_name;
	}
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
	char	*expanded_file_name;

	original_stdout = dup(STDOUT_FILENO);
	if (node->right->token_node->token->value[0] == '$') {
		expanded_file_name = env_value_expand(shell->env_list, node->right->token_node->token->value);
		free(node->right->token_node->token->value);
		if (expanded_file_name == NULL)
			node->right->token_node->token->value = ft_strdup("");
		else
			node->right->token_node->token->value = expanded_file_name;
	}
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