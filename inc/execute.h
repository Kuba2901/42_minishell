/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:00:10 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:48:02 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <mini_base.h>
# include <errno.h>
# include <environment.h>
# include <builtins.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <ast.h>
# define HEREDOC_FILE_TEMPLATE "/tmp/minishell_heredoc_"

typedef struct s_shell	t_shell;

typedef struct s_heredoc_data
{
	pid_t		pid;
	t_ast_node	*node;
	t_shell		*shell;
	int			pipe_fd[2];
	int			original_stdin;
}	t_heredoc_data;

char	*execute_find_executable(char *command, t_shell *shell);
void	execute_command_node(t_shell *shell, t_ast_node *node);
void	execute_ast(t_shell *shell, t_ast_node *node);
void	execute_redirect_in(t_shell *shell, t_ast_node *node);
void	execute_pipe(t_shell *shell, t_ast_node *node);
void	execute_redirect_append(t_shell *shell, t_ast_node *node);
void	execute_redirect_out(t_shell *shell, t_ast_node *node);
void	execute_preprocess_heredocs(t_ast_node *node);
int		execution_redirect_open_file(t_shell *shell, t_ast_node *node);

#endif