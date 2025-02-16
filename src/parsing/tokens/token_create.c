/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:07:33 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:39:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

/**
 * @brief Initializes a new token node with the given type and value.
 *
 * This function allocates memory for a new token node and initializes its
 * fields based on the provided type and value. If the type is TOKEN_STRING
 * and a non-NULL value is provided, it also allocates memory for the args
 * field and duplicates the value into the first element of the args array.
 *
 * @param type The type of the token.
 * @param value The value of the token, used if the type is TOKEN_STRING.
 * @return A pointer to the newly created token node, or NULL if memory
 *         allocation fails.
 */
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
