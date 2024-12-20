/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:07:21 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/15 17:34:07 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parsing.h>
# include <utils.h>
# include <execution.h>
# define DOUBLE_SPECIAL_CHARSET "|&<>"
# define SINGLE_SPECIAL_CHARSET "="
# define PROMPT "minishell > "

typedef struct  s_mini
{
	t_env_list		*env_list;
	t_token_list	*tokens_list;
	t_ast_node		*head;
}               t_mini;

#endif