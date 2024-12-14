/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:26 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/02 18:30:17 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

t_ast_node	*parse_redirect_out(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*redirect_node;

	left = parse_command(tokens);
	if (tokens->head && tokens->head->token->type == TOKEN_REDIRECT_OUT)
	{
		tokens->head = tokens->head->next;
		right = parse_command(tokens);
		redirect_node = create_ast_node(AST_REDIRECT_OUT, NULL);
		redirect_node->left = left;
		redirect_node->right = right;
		return (redirect_node);
	}
	return (left);
}

t_ast_node	*parse_redirect_in(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*redirect_node;

	left = parse_command(tokens);
	if (tokens->head && tokens->head->token->type == TOKEN_REDIRECT_IN)
	{
		tokens->head = tokens->head->next;
		right = parse_command(tokens);
		redirect_node = create_ast_node(AST_REDIRECT_IN, NULL);
		redirect_node->left = left;
		redirect_node->right = right;
		return (redirect_node);
	}
	return (left);
}

t_ast_node	*parse_append(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*redirect_node;

	left = parse_command(tokens);
	if (tokens->head && tokens->head->token->type == TOKEN_APPEND)
	{
		tokens->head = tokens->head->next;
		right = parse_command(tokens);
		redirect_node = create_ast_node(AST_APPEND, NULL);
		redirect_node->left = left;
		redirect_node->right = right;
		return (redirect_node);
	}
	return (left);
}

t_ast_node	*parse_heredoc(t_token_list *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*redirect_node;

	left = parse_command(tokens);
	if (tokens->head && tokens->head->token->type == TOKEN_HEREDOC)
	{
		tokens->head = tokens->head->next;
		right = parse_command(tokens);
		redirect_node = create_ast_node(AST_HEREDOC, NULL);
		redirect_node->left = left;
		redirect_node->right = right;
		return (redirect_node);
	}
	return (left);
}
