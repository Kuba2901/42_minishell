/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:12:42 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/29 12:01:16 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <environment.h>
# include <ast.h>

typedef struct  s_mini
{
	t_env_list		*env_list;
	t_token_list	*tokens_list;
	t_ast_node		*head;
	int				in_fd;
	int				out_fd;
	pid_t			pid;
}               t_mini;

char	*find_executable(const char *command, t_env_list *env_list);

#endif

