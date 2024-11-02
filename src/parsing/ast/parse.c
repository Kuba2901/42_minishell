/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:41 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 21:02:24 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

// t_ast_node	*create_ast_node(t_ast_node_type type, char *value)
// {
// 	t_ast_node	*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = type;
// 	if (value != NULL)
// 		node->value = ft_strdup(value);
// 	else
// 		node->value = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }



// t_ast_node	*parse_command(t_token_list *tokens)
// {
// 	t_ast_node	*node;
	
// 	if (tokens->head == NULL)
// 		return (NULL);
// 	if (tokens->head->token->type == TOKEN_WORD)
// 	{
// 		// node = create_as
// 	}
// }