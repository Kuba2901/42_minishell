#include <execution.h>

void execute_redirect_heredoc(t_ast_node *node, t_mini *shell)
{
    int pipe_fd[2];
    char *line;
    char *delimiter;
    int original_stdin;
    pid_t pid;

    if (!node || !node->right || !node->right->token_node) {
        fprintf(stderr, "heredoc: invalid syntax\n");
        return;
    }

    delimiter = node->right->token_node->token->value;
    if (!delimiter) {
        fprintf(stderr, "heredoc: missing delimiter\n");
        return;
    }

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return;
    }

    original_stdin = dup(STDIN_FILENO); // Save original stdin

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0)  // Child process: Read input and write to pipe
    {
        close(pipe_fd[0]); // Close read-end, only writing

        while (1) {
            line = readline("> ");
            if (!line) break;

            // Stop reading if the delimiter is found
            if (strcmp(line, delimiter) == 0) {
                free(line);
                break;
            }

            write(pipe_fd[1], line, strlen(line));
            write(pipe_fd[1], "\n", 1);
            free(line);
        }
        close(pipe_fd[1]); // Close write-end
        exit(EXIT_SUCCESS); // Only child process exits
    }
    else  // Parent process: Redirect stdin and execute command
    {
        int status;
        waitpid(pid, &status, 0); // Wait for heredoc input process

        close(pipe_fd[1]); // Close write-end, only reading
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipe_fd[0]);

        // Execute the next command
        execute_ast(node->left, shell);

        // Restore original stdin
        dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);
    }
}