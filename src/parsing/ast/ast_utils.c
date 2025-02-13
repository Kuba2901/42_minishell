/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:10:22 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:42:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

static void	print_ast_indent(t_ast_node *node, int indent)
{
	if (node == NULL)
		return;
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (node->type == TOKEN_STRING)
		printf("%s\n", node->token_node->args[0]);
	else if (node->type == TOKEN_PIPE)
	{
		printf("Pipe:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == TOKEN_REDIRECT_OUT)
	{
		printf(">:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == TOKEN_APPEND)
	{
		printf(">>:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == TOKEN_REDIRECT_IN)
	{
		printf("<:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == TOKEN_HEREDOC)
	{
		printf("<<:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
}

/**
 * @brief Prints the abstract syntax tree (AST) starting
 * from the given node.
 *
 * This function prints the abstract syntax tree (AST)
 * starting from the given node.
 * It uses indentation to represent the hierarchical structure of the AST.
 *
 * @param node The root node of the AST to be printed.
 */
void	ast_print(t_ast_node *node)
{
	print_ast_indent(node, 0);
}
