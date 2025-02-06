/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:12:42 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/29 12:12:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <ast.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <environment.h>
# include <errno.h>

typedef struct  s_mini
{
	t_env_list		*env_list;
	t_token_list	*tokens_list;
	t_ast_node		*head;
	int				in_fd;
	int				out_fd;
	pid_t			pid;
	int				last_exit_status;
}               t_mini;

typedef struct	s_heredoc_data
{
	pid_t		pid;
	t_ast_node	*node;
	t_mini		*shell;
	int			pipe_fd[2];
	int			original_stdin;
}	t_heredoc_data;

char	*find_executable(const char *command, t_env_list *env_list);
void	execute_command_node(t_ast_node *node, t_mini *shell, t_bool is_another_process);
void	execute_pipe(t_ast_node *node, t_mini *shell);
void	execute_ast(t_ast_node *node, t_mini *shell);
void	execute_redirect_out(t_ast_node *node, t_mini *shell);
void	execute_redirect_in(t_ast_node *node, t_mini *shell);
void	execute_redirect_append(t_ast_node *node, t_mini *shell);
void	execute_redirect_heredoc(t_ast_node *node, t_mini *shell);

#endif

