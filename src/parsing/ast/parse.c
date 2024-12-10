/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:36:05 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/10 20:21:23 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
/**
 * @brief Creates a new AST node.
 *
 * This function allocates memory for a new `t_ast_node` structure and initializes its fields.
 * The `type` parameter specifies the type of the node, while the `value` parameter specifies the value associated with the node.
 * If `value` is `NULL`, the `value` field of the node will be set to `NULL`.
 *
 * @param type The type of the AST node.
 * @param value The value associated with the AST node.
 * @return A pointer to the newly created `t_ast_node` structure, or `NULL` if memory allocation fails.
*/

/* PARSING ALGORITHM
1. Go right until an and is found (outside any parenthesis)
	> If an '&&' is found, parse everything to the left, looking for a '||'
	> If no '&&' is found, proceed
2. Go right until an '||' is found (outside any parenthesis)
	> If an '||' is found, parse everything to the left, looking for a '|'
	> If no '||' is found, proceed
3. Go right until a '|' is found
	> If a '|' is found, parse everything to the left, looking for a redirect
	> If no '|' is found, proceed
4. Go right until a redirect is found (outside any parenthesis)
	> If a redirect is found, parse everything to the left, looking for a command
	> If no redirect is found, proceed
5. Parse the command
	> If a command is found, create a command node
	> If no command is found, return an error
*/

t_ast_node	*create_ast_node(t_ast_node_type type, t_token_node *token_node)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (token_node != NULL)
		node->token_node = token_node;
	else
		node->token_node = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}


// t_ast_node	*build_ast(t_token_list *list)
// {
// 	t_ast_node	*node;

// 	if (!list->head)
// 		return ;
	
// }

t_ast_node	*parse_command(t_token_list *tokens)
{
	t_ast_node	*node;

	if (tokens->head == NULL)
		return (NULL);
	if (tokens->head->token->type == TOKEN_WORD)
	{
		node = create_ast_node(AST_COMMAND, tokens->head);
		tokens->head = tokens->head->next;
		return (node);
	}
	return (NULL);
}

t_ast_node	*parse_pipe(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	left = parse_command(tokens);
	while (tokens->head && tokens->head->token->type == TOKEN_PIPE)
	{
		tokens->head = tokens->head->next;
		right = parse_command(tokens);
		pipe_node = create_ast_node(AST_PIPE, NULL);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

// t_ast_node	*parse_pipe(t_token_list *list)
// {
// 	t_ast_node	*node;

// 	if (!list || !list->head)
// 		return (NULL);
// 	if (list->head->token->type == TOKEN_PIPE)
// 	{
// 		node->left = parse_command(list);
// 	}
// }


// t_ast_node	*parse_pipe(t_token_list *tokens)
// {
// 	t_ast_node	*left;
// 	t_ast_node	*right;
// 	t_ast_node	*pipe_node;

// 	left = parse_redirect_out_append(tokens);
// 	while (tokens->head && tokens->head->token->type == TOKEN_PIPE)
// 	{	
// 		tokens->head = tokens->head->next;
// 		right = primary_parse(tokens);
// 		pipe_node = create_ast_node(AST_PIPE, NULL);
// 		pipe_node->left = left;
// 		pipe_node->right = right;
// 		left = pipe_node;
// 	}
// 	return (left);
// }

// t_ast_node	*parse_and(t_token_list *list)
// {
// 	t_bool		is_in_paren;
// 	t_ast_node	*left;
// 	t_ast_node	*right;

// 	left = parse_or(list);
// 	is_in_paren = false;
// 	while (list->head && list->head != )
// }

// t_ast_node	*parse_or(t_token_list *list)
// {
// 	t_bool		is_in_paren;
// 	t_ast_node	*left;
// 	t_ast_node	*right;
	
// 	left = parse_pipe(list);
// }



static void print_ast_indent(t_ast_node *node, int indent)
{
	if (node == NULL)
		return;

	// Print indentation spaces
	for (int i = 0; i < indent; i++)
		printf("  ");

	// Print the node based on its type
	if (node->type == AST_COMMAND)
	{
		printf("%s\n", node->token_node->token->value);
	}
	else if (node->type == AST_PIPE)
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
	else if (node->type == AST_AND)
	{
		printf("And:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == AST_OR)
	{
		printf("Or:\n");
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast_indent(node->left, indent + 2);
		for (int i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast_indent(node->right, indent + 2);
	}
	else if (node->type == AST_REDIRECT_OUT)
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
	else if (node->type == AST_APPEND)
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
}

/**
 * @brief Prints the abstract syntax tree (AST) starting from the given node.
 *
 * This function prints the abstract syntax tree (AST) starting from the given node.
 * It uses indentation to represent the hierarchical structure of the AST.
 *
 * @param node The root node of the AST to be printed.
 */
void print_ast(t_ast_node *node)
{
	print_ast_indent(node, 0);
}


/**
 * @brief Frees the memory allocated for an abstract syntax tree (AST) node.
 *
 * This function recursively frees the memory allocated for an AST node and its children.
 * If the node is NULL, the function returns without performing any action.
 *
 * @param node The AST node to be freed.
 */
void	free_ast(t_ast_node *node)
{
	if (node == NULL)
		return;
	if (node->token_node)
	{
		free_token(node->token_node->token);
		free(node->token_node);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}