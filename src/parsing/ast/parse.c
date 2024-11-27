/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:41 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/22 17:06:58 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
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

t_ast_node	*create_ast_node(t_ast_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/**
 * Parses a command from a token list.
 *
 * @param tokens The token list to parse.
 * @return The parsed command as an abstract syntax tree (AST) node.
 *         Returns NULL if the token list is empty or the first token is not of type TOKEN_WORD.
 */
t_ast_node	*parse_command(t_token_list *tokens)
{
	t_ast_node	*node;

	if (tokens->head == NULL)
		return (NULL);
	if (tokens->head->token->type == TOKEN_WORD)
	{
		node = create_ast_node(AST_COMMAND, tokens->head->token->value);
		tokens->head = tokens->head->next;
		return (node);
	}
	return (NULL);
}

/**
 * Parses the tokens and constructs an abstract syntax tree (AST) for redirecting output with append or overwrite.
 *
 * @param tokens The token list to parse.
 * @return The root node of the constructed AST.
*/
t_ast_node	*parse_redirect_out_append(t_token_list *tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*node;
	t_ast_node_type	type;

	left = parse_command(tokens);
	while (tokens->head \
		&& (tokens->head->token->type == TOKEN_APPEND \
		|| tokens->head->token->type == TOKEN_REDIRECT_OUT))
	{
		if (tokens->head->token->type == TOKEN_APPEND)
			type = AST_APPEND;
		else
			type = AST_REDIRECT_OUT;
		tokens->head = tokens->head->next;
		right = parse_command(tokens); // TODO: To be verified (might be primary_parse)
		node = create_ast_node(type, NULL);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

/**
 * @brief Parses the pipe operator in the abstract syntax tree (AST).
 *
 * This function takes a token list as input and parses the pipe operator
 * in the AST. It iterates through the token list and creates AST nodes for
 * each pipe operator encountered. The left and right operands of the pipe
 * operator are obtained by calling the respective parsing functions. The
 * AST node for the pipe operator is then created and linked to the left and
 * right operands. The function returns the root node of the resulting AST.
 *
 * @param tokens The token list to parse.
 *
 * @return The root node of the resulting AST.
 */
t_ast_node	*parse_pipe(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	left = parse_redirect_out_append(tokens);
	while (tokens->head && tokens->head->token->type == TOKEN_PIPE)
	{
		tokens->head = tokens->head->next;
		right = primary_parse(tokens);
		pipe_node = create_ast_node(AST_PIPE, NULL);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

/**
 * @brief Parses the logical operators in the abstract syntax tree (AST).
 *
 * This function takes a token list as input and parses the logical operators
 * (AND and OR) in the AST. It iterates through the token list and creates AST
 * nodes for each logical operator encountered. The left and right operands of
 * the logical operator are obtained by calling the respective parsing functions.
 * The AST node for the logical operator is then created and linked to the left
 * and right operands. The function returns the root node of the resulting AST.
 *
 * @param tokens The token list to parse.
 * @return The root node of the resulting AST.
 */
t_ast_node	*parse_logical(t_token_list *tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*op_node;
	t_token_type	type;

	left = parse_pipe(tokens);
	while (tokens->head != NULL \
		&& ((tokens->head->token->type == TOKEN_AND) \
			|| (tokens->head->token->type == TOKEN_OR)))
	{
		type = tokens->head->token->type;
		tokens->head = tokens->head->next;
		right = primary_parse(tokens);
		// TODO: Fix for this input `echo test && ls | grep ".txt" || cat /etc/passwd` the OR should be higher than the AND in the AST
		if (type == TOKEN_AND)
			op_node = create_ast_node(AST_AND, NULL);
		else
			op_node = create_ast_node(AST_OR, NULL);
		op_node->left = left;
		op_node->right = right;
		left = op_node;
	}
	return (left);
}

/**
 * @brief Parses the primary expression in the abstract syntax tree (AST).
 *
 * This function takes a token list as input and parses the primary expression
 * in the AST. If the token list is empty, it returns NULL. If the first token
 * in the list is a left parenthesis, it advances the token list and calls the
 * parse_logical function recursively. After parsing the logical expression, it
 * checks if the next token is a right parenthesis. If it is not, it prints an
 * error message and returns NULL. If the next token is a right parenthesis, it
 * advances the token list and returns the parsed logical expression. If the
 * first token is not a left parenthesis, it calls the parse_logical function
 * directly.
 *
 * @param tokens The token list to be parsed.
 * @return A pointer to the parsed AST node.
 */
t_ast_node *primary_parse(t_token_list *tokens)
{
	t_ast_node	*node;

	if (tokens->head == NULL)
		return (NULL);
	if (tokens->head->token->type == TOKEN_LPAREN)
	{
		tokens->head = tokens->head->next;
		node = parse_logical(tokens);
		if (tokens->head == NULL || tokens->head->token->type != TOKEN_RPAREN)
		{
			printf("Error: Expected ')'\n");
			return (NULL);
		}
		tokens->head = tokens->head->next;
		return (node);
	}
	return (parse_logical(tokens));
}

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
		printf("%s\n", node->value);
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
		return ;
	if (node->value)
		free(node->value);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}