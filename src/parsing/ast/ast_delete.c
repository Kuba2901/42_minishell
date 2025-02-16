/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:09:29 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:35:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

/**
 * @brief Recursively deletes an Abstract Syntax Tree (AST) node and its children.
 *
 * This function takes a pointer to an AST node and recursively deletes its left 
 * and right children, as well as the token associated with the node. Finally, 
 * it frees the memory allocated for the node itself.
 *
 * @param node A pointer to the AST node to be deleted. If the node is NULL, 
 *             the function returns immediately.
 */
void	ast_delete(t_ast_node *node)
{
	if (!node)
		return ;
	ast_delete(node->left);
	ast_delete(node->right);
	token_delete(node->token_node);
	free(node);
}
