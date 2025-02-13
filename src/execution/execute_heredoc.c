/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:28:07 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:58:41 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <minishell.h>

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
