/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:36:11 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/10 20:30:14 by jnenczak         ###   ########.fr       */
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

/**
 * Creates a token with the specified type and value.
 *
 * @param type The type of the token.
 * @param value The value of the token.
 * @return A pointer to the created token.
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	if (value)
	{
		// TODO: Expand the value
		// if (value[0] == '$')
		// {
		// }
		token->value = ft_strdup(value);
	}
	else
		token->value = NULL;
	token->args = NULL;
	return (token);
}
/**
 * @brief Frees the memory allocated for a token.
 *
 * This function frees the memory allocated for a token and its value.
 *
 * @param token The token to be freed.
 */
void	free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}
