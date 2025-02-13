/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_redirect_out.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:11:54 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:12:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * ast_create_redirect_out_append - Parses a list of tokens to
 * create an AST node for redirect out or append operations.
 * 
 * @list: A pointer to the head of the token list.
 *
 * This function processes a list of tokens to create an
 * abstract syntax tree (AST)
 * node representing redirect out (>) or append (>>) operations.
 * It starts by
 * creating a command node from the token list and then iterates
 * through the list
 * to handle consecutive redirect out or append tokens. For each
 * such token, it
 * creates a new AST node, sets the left and right children, and
 * updates the left
 * child to the newly created node. The function returns the
 * final AST node
 * representing the parsed redirect out or append operations.
 *
 * Return: A pointer to the root of the created AST node.
 */
t_ast_node	*ast_create_redirect_out_append(t_token_node **list)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*node;
	t_token_node	*head;

	left = ast_create_command(list);
	head = *list;
	while (head \
		&& (head->type == TOKEN_APPEND \
		|| head->type == TOKEN_REDIRECT_OUT))
	{
		*list = head->next;
		right = ast_create_command(list);
		node = ast_create_node(head);
		node->left = left;
		node->right = right;
		left = node;
		head = *list;
	}
	return (left);
}
