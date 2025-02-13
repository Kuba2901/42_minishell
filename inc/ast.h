/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:59:51 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:59:57 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <mini_base.h>
# include <tokens.h>

typedef struct s_ast_node
{
	t_token_type		type;
	t_token_node		*token_node;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*ast_create_command(t_token_node **list);
t_ast_node	*ast_create_node(t_token_node *token_node);
t_ast_node	*ast_create_pipe(t_token_node **list);
t_ast_node	*ast_create_redirect_in_heredoc(t_token_node **list);
t_ast_node	*ast_create_redirect_out_append(t_token_node **list);
t_ast_node	*ast_create_redirect(t_token_node **list);
t_ast_node	*ast_create(t_token_node **list);
void		ast_delete(t_ast_node *node);
void		ast_print(t_ast_node *node);

#endif