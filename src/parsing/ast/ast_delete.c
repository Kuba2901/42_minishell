/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:09:29 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:09:30 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

void	ast_delete(t_ast_node *node)
{
	if (!node)
		return ;
	ast_delete(node->left);
	ast_delete(node->right);
	token_delete(node->token_node);
	free(node);
}
