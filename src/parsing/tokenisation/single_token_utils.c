/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:36:11 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 21:03:05 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

const char	*get_token_description(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("command");
	else if (type == TOKEN_AND)
		return ("&&");
	else if (type == TOKEN_OR)
		return ("||");
	else if (type == TOKEN_LPAREN)
		return ("(");
	else if (type == TOKEN_RPAREN)
		return (")");
	else if (type == TOKEN_PIPE)
		return ("|");
	else if (type == TOKEN_REDIRECT_IN)
		return ("<");
	else if (type == TOKEN_REDIRECT_OUT)
		return (">");
	else if (type == TOKEN_APPEND)
		return (">>");
	else if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("unknown");
}

t_bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	return (token);
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}
