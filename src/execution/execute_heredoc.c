/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:28:07 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:32:45 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

/**
 * @brief Creates a temporary file name using a template and the process ID.
 *
 * This function generates a unique temporary file name by appending the
 * current process ID to a predefined template string. The resulting file
 * name is dynamically allocated and should be freed by the caller when no
 * longer needed.
 *
 * @return A pointer to the dynamically allocated string containing the
 *         temporary file name. The caller is responsible for freeing this
 *         memory.
 *
 * @note If memory allocation fails, the function prints an error message
 *       and terminates the program.
 */
static char	*_create_temp_file_name(void)
{
	char	*temp_filename;
	char	*pid_str;
	int		template_len;
	int		i;

	pid_str = ft_itoa(getpid());
	template_len = (int)ft_strlen(HEREDOC_FILE_TEMPLATE);
	temp_filename = malloc(sizeof(char)
			* (template_len + ft_strlen(pid_str) + 1));
	if (!temp_filename)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < template_len)
		temp_filename[i] = HEREDOC_FILE_TEMPLATE[i];
	i = -1;
	while (pid_str[++i])
		temp_filename[template_len + i] = pid_str[i];
	temp_filename[template_len + i] = '\0';
	free(pid_str);
	return (temp_filename);
}

/**
 * @brief Trims the leading and trailing quotes from a given string.
 *
 * This function checks if the input string starts and ends with the same type of quote
 * (either single quote ' or double quote "). If so, it allocates memory for a new string
 * that excludes these quotes and returns it. If the input string does not start and end
 * with the same type of quote, it returns a duplicate of the original string.
 *
 * @param str The input string to be trimmed.
 * @return A new string with the leading and trailing quotes removed, or a duplicate of the original string if no quotes are found.
 */
static char	*trim_quotes(char *str)
{
	size_t	len;
	char	*trimmed_str;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') \
		|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		trimmed_str = malloc(sizeof(char) * (len - 1));
		if (!trimmed_str)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strncpy(trimmed_str, str + 1, len - 2);
		trimmed_str[len - 2] = '\0';
		return (trimmed_str);
	}
	return (ft_strdup(str));
}

/**
 * @brief Processes input for a heredoc and writes it to a temporary file.
 *
 * This function reads lines from the standard input until a line matching the
 * specified delimiter is encountered. Each line is written to the specified
 * temporary file. The temporary file is created if it does not exist, and
 * truncated if it does.
 *
 * @param temp_filename The name of the temporary file to write the heredoc input to.
 * @param delimiter The delimiter string that indicates the end of the heredoc input.
 *
 * @note If temp_filename is NULL or if the file cannot be opened, the function
 *       will exit with EXIT_FAILURE.
 */
void	process_heredoc_input(char *temp_filename, const char *delimiter)
{
	int		fd;
	char	*line;

	if (!temp_filename)
		exit(EXIT_FAILURE);
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

/**
 * @brief Preprocesses heredoc nodes in the abstract syntax tree (AST).
 *
 * This function recursively traverses the AST and processes nodes of type
 * TOKEN_HEREDOC. For each such node, it trims the quotes from the delimiter,
 * creates a temporary file name, processes the heredoc input, and updates the
 * node type to TOKEN_REDIRECT_IN. It also updates the node's arguments to
 * point to the temporary file name.
 *
 * @param node A pointer to the current AST node being processed.
 */
void	execute_preprocess_heredocs(t_ast_node *node)
{
	char	*delimiter;
	char	*temp_filename;

	if (!node)
		return ;
	if (node->type == TOKEN_HEREDOC)
	{
		delimiter = trim_quotes(node->right->token_node->args[0]);
		temp_filename = _create_temp_file_name();
		process_heredoc_input(temp_filename, delimiter);
		node->type = TOKEN_REDIRECT_IN;
		free(node->right->token_node->args[0]);
		node->right->token_node->args[0] = temp_filename;
		free(delimiter);
	}
	execute_preprocess_heredocs(node->left);
	execute_preprocess_heredocs(node->right);
}
