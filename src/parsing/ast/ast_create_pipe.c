/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:40:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * ast_create_pipe - Creates an AST node for a pipe operation.
 * @list: A pointer to the list of token nodes.
 *
 * This function creates an abstract syntax tree (AST) node for a pipe operation
 * by parsing the token list. It first creates the left node by calling
 * ast_create_redirect. Then, it iterates through the token list to find pipe
 * tokens (TOKEN_PIPE). For each pipe token found, it creates a right node by
 * calling ast_create, and then creates a pipe node with the current token. The
 * left and right nodes are assigned to the pipe node, and the left node is
 * updated to the pipe node. The function returns the final left node, which
 * represents the root of the pipe operation AST.
 *
 * Return: A pointer to the root AST node of the pipe operation.
 */
t_ast_node	*ast_create_pipe(t_token_node **list)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*pipe_node;
	t_token_node	*head;

	left = ast_create_redirect(list);
	head = *list;
	while (head && head->type == TOKEN_PIPE)
	{
		*list = head->next;
		right = ast_create(list);
		pipe_node = ast_create_node(head);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
		head = *list;
	}
	return (left);
}
