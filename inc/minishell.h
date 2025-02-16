/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:04 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:43:14 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <mini_base.h>
# include <environment.h>
# include <tokens.h>
# include <ast.h>
# include <execute.h>
# include <aesthetics.h>
# define PROMPT "\033[35m minishell > \033[0m"

typedef struct s_shell
{
	t_environment_node	*env;
	int					exit_code;
	const char			**envp;
	t_bool				top_level_redir_out_enabled;
	t_bool				top_level_redir_in_enabled;
}	t_shell;

#endif