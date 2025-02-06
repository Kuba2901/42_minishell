#include <execution.h>

static void	_execute_pipe_read(t_heredoc_data *data)
{
	char	*line;

	close(data->pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line) break;
		if (!strcmp(line, data->node->right->token_node->token->value)) // TODO: Change to ft_strncmp
		{
			free(line);
			break;
		}
		write(data->pipe_fd[1], line, strlen(line));
		write(data->pipe_fd[1], "\n", 1);
		free(line);
	}
	close(data->pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static void	_execute_pipe_write(t_heredoc_data *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	close(data->pipe_fd[0]);
	execute_ast(data->node->left, data->shell);
	dup2(data->original_stdin, STDIN_FILENO);
	close(data->original_stdin);
}

void	execute_redirect_heredoc(t_ast_node *node, t_mini *shell)
{
	t_heredoc_data	data;
	char			*delimiter;

	if (!node || !node->right || !node->right->token_node)
		return ;
	delimiter = node->right->token_node->token->value;
	if (!delimiter)
		return ;
	if (pipe(data.pipe_fd) == -1)
		return ;
	data.original_stdin = dup(STDIN_FILENO);
	data.node = node;
	data.shell = shell;
	data.pid = fork();
	if (data.pid == -1)
		return ;
	if (data.pid == 0)
		_execute_pipe_read(&data);
	else
		_execute_pipe_write(&data);
}