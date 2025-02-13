/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:01 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:21:03 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <libft.h>

/**
 * ast_create_redirect - Parses a list of tokens to create an
 * abstract syntax tree (AST) node
 *                  representing a redirection.
 * @list: A pointer to the list of tokens to be parsed.
 *
 * This function parses a list of tokens to create an AST node that represents
 * a redirection operation. It first parses the left-hand side command, then
 * iterates through the list of tokens to check for redirection operators
 * (heredoc, redirect in, append, redirect out). For each redirection operator
 * found, it creates a new AST node, sets the left and right children, and
 * updates the list pointer to the next token. The function returns the root
 * of the created AST subtree.
 *
 * Return: A pointer to the root AST node representing the redirection.
 */
/*
*/
t_ast_node	*ast_create_redirect(t_token_node **list)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*node;
	t_token_node	*head;

	left = ast_create_command(list);
	head = *list;
	while (head \
		&& (head->type == TOKEN_HEREDOC \
		|| head->type == TOKEN_REDIRECT_IN \
		|| head->type == TOKEN_APPEND \
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
