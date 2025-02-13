/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:09:35 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:10:11 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * ast_parse_command - Parses a command from a token
 * list and creates an AST node.
 * @list: A double pointer to the head of the token list.
 *
 * This function checks if the provided token list is valid
 * and if the head of the
 * list is of type TOKEN_STRING. If so, it creates an AST
 * node from the head token,
 * advances the list to the next token, and returns the
 * created AST node. If the
 * list is invalid or the head token is not of type
 * TOKEN_STRING, it returns NULL.
 *
 * Return: A pointer to the created AST node, or NULL if
 * the list is invalid or the head token is not of type TOKEN_STRING.
 */
t_ast_node	*ast_create_command(t_token_node **list)
{
	t_token_node	*head;
	t_ast_node		*node;

	if (!list || !*list)
		return (NULL);
	head = *list;
	if (head->type == TOKEN_STRING)
	{
		node = ast_create_node(head);
		*list = head->next;
		return (node);
	}
	return (NULL);
}
