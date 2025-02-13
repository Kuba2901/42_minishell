/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:12:48 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:41:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * @brief Creates a new AST node.
 *
 * This function allocates memory for a new `t_ast_node`
 * structure and initializes its fields.
 * The `type` parameter specifies the type of the node, while the `value`
 * parameter specifies the value associated with the node.
 * If `value` is `NULL`, the `value` field of the node will be set to `NULL`.
 *
 * @param type The type of the AST node.
 * @param value The value associated with the AST node.
 * @return A pointer to the newly created `t_ast_node` structure,
 * or `NULL` if memory allocation fails.
 */

t_ast_node	*ast_create_node(t_token_node *token_node)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token_node->type;
	node->token_node = token_node;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/**
 * @brief Creates an abstract syntax tree (AST) from a list of tokens.
 *
 * This function takes a list of tokens and constructs an AST node from it.
 * If the list is empty or NULL, the function returns NULL.
 * Otherwise, it delegates the creation of the AST to the
 * `ast_create_pipe` function.
 *
 * @param list A pointer to the list of tokens to be parsed into an AST.
 * @return A pointer to the created AST node, or NULL if the list is
 * empty or NULL.
 */
t_ast_node	*ast_create(t_token_node **list)
{
	if (!list || !*list)
		return (NULL);
	return (ast_create_pipe(list));
}
