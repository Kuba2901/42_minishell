/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:07:33 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:07:57 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

static t_token_node	*_token_initialize(t_token_type type, char *value)
{
	t_token_node	*token;

	token = malloc(sizeof(t_token_node));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	if (type == TOKEN_STRING && value != NULL)
	{
		token->args = malloc(sizeof(char *) * 2);
		if (!token->args)
		{
			free(token);
			return (NULL);
		}
		token->args[0] = ft_strdup(value);
		token->args[1] = NULL;
	}
	else
		token->args = NULL;
	return (token);
}

/**
 * @brief Creates a new token node with the specified type and value.
 *
 * This function initializes a new token node using the provided type and value.
 * If the initialization fails, it returns NULL.
 *
 * @param type The type of the token.
 * @param value The value of the token.
 * @return A pointer to the newly created token node,
 * or NULL if initialization fails.
 */
t_token_node	*token_create(t_token_type type, char *value)
{
	t_token_node	*token;

	token = _token_initialize(type, value);
	if (!token)
		return (NULL);
	return (token);
}
