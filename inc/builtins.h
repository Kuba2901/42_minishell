/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:59:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:09:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <mini_base.h>
# include <tokens.h>
# define BUILTIN_EXIT_TOO_MANY_ARGS -1
# define BUILTIN_EXIT_NON_NUMERIC_ARG 2
# define BUILTIN_EXIT_OK 0

typedef struct s_shell		t_shell;
typedef struct s_ast_node	t_ast_node;

char	*builtin_pwd(void);
void	execute_builtin_pwd(t_shell *shell);
void	builtin_env(t_shell *shell);
void	builtin_unset(t_shell *shell, t_ast_node *node);
void	builtin_set_private(t_shell *shell, t_ast_node *node);
void	builtin_export(t_shell *shell, t_ast_node *node);
t_bool	builtin_export_export_key_value(t_shell *shell, t_ast_node *node);
t_bool	builtin_exit(t_shell *shell, t_ast_node **node_ptr, char **line_ptr,
			t_token_node ***list_ptr);
void	builtin_echo(t_shell *shell, t_ast_node *node);
void	builtin_cd(t_shell *shell, char **args);

#endif