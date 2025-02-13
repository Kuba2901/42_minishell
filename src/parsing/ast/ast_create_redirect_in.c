/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_redirect_in.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:11:08 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:11:46 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * ast_create_redirect_in_heredoc - Parses a list of tokens
 * to create an AST node for input redirection and heredoc.
 * 
 * @list: Double pointer to the head of the token list.
 *
 * This function processes a list of tokens to create an
 * abstract syntax tree (AST)
 * node for input redirection and heredoc. It starts by
 * creating a command node
 * from the token list and then iterates through the list to
 * handle heredoc and
 * input redirection tokens. For each heredoc or input redirection
 * token, it creates
 * a new AST node, sets the left and right children, and updates the
 * left node to
 * the newly created node. The function returns the final left node,
 * which represents
 * the root of the constructed AST for input redirection and heredoc.
 *
 * Return: A pointer to the root of the constructed AST node.
 */
t_ast_node	*ast_create_redirect_in_heredoc(t_token_node **list)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*node;
	t_token_node	*head;

	left = ast_create_command(list);
	head = *list;
	while (head \
		&& (head->type == TOKEN_HEREDOC \
		|| head->type == TOKEN_REDIRECT_IN))
	{
		*list = head->next;
		right = ast_create_command(list);
		node = ast_create_node(head);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}
