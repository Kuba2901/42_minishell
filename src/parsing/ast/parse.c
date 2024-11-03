/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:41 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 16:58:04 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

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

// static t_ast_node	*parse_redirect_handler(t_token_list *tokens, t_ast_node *left, t_token_type type)
// {
// 	t_ast_node	*right;
// 	t_ast_node	*op_node;

// 	right = primary_parse(tokens);
// 	if (type == TOKEN_REDIRECT_IN)
// 		op_node = create_ast_node(AST_REDIRECT_IN, NULL);
// 	else if (type == TOKEN_REDIRECT_OUT)
// 		op_node = create_ast_node(AST_REDIRECT_OUT, NULL);
// 	else if (type == TOKEN_APPEND)
// 		op_node = create_ast_node(AST_APPEND, NULL);
// 	else if (type == TOKEN_HEREDOC)
// 		op_node = create_ast_node(AST_HEREDOC, NULL);
// 	op_node->left = left;
// 	op_node->right = right;
// 	return (op_node);
// }

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

t_ast_node	*parse_pipe(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	left = parse_redirect_out_append(tokens);
	// left = parse_command(tokens);
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

/*
t_ast_node	*parse_redirect(t_token_list *tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*op_node;
	t_token_type	type;

	left = parse_pipe(tokens);
	while (tokens->head != NULL \
		&& ((tokens->head->token->type == TOKEN_REDIRECT_IN) \
			|| (tokens->head->token->type == TOKEN_REDIRECT_OUT) \
			|| (tokens->head->token->type == TOKEN_APPEND) \
			|| (tokens->head->token->type == TOKEN_HEREDOC)))
	{
		type = tokens->head->token->type;
		tokens->head = tokens->head->next;
		right = primary_parse(tokens);
		if (type == TOKEN_REDIRECT_IN)
			op_node = create_ast_node(AST_REDIRECT_IN, NULL);
		else if (type == TOKEN_REDIRECT_OUT)
			op_node = create_ast_node(AST_REDIRECT_OUT, NULL);
		else if (type == TOKEN_APPEND)
			op_node = create_ast_node(AST_APPEND, NULL);
		else if (type == TOKEN_HEREDOC)
			op_node = create_ast_node(AST_HEREDOC, NULL);
		op_node->left = left;
		op_node->right = right;
		left = op_node;
	}
	return (left);
}
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

t_ast_node	*primary_parse(t_token_list *tokens)
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

void print_ast(t_ast_node *node)
{
	print_ast_indent(node, 0);
}


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