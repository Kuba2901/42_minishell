/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:04:23 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:04:49 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

/**
 * @brief Frees the memory allocated for a token and its arguments.
 *
 * This function releases the memory allocated for the arguments of a token
 * and then frees the memory allocated for the token itself.
 *
 * @param token A pointer to the token to be deleted.
 */
void	token_delete(t_token_node *token)
{
	int	i;

	if (token->args)
	{
		i = -1;
		while (token->args[++i])
		{
			free(token->args[i]);
			token->args[i] = NULL;
		}
	}
	free(token->args);
	token->args = NULL;
	free(token);
}

/**
 * @brief Frees the memory allocated for a list of tokens.
 *
 * This function iterates through a linked list of tokens, freeing the memory
 * allocated for each token and its arguments. It then frees the memory
 * allocated for the list itself.
 *
 * @param list A double pointer to the head of the list of tokens to be deleted.
 */
void	token_delete_all(t_token_node **list)
{
	t_token_node	*next;
	t_token_node	*token;

	if (!list || !*list)
		return ;
	token = *list;
	while (token)
	{
		next = token->next;
		token_delete(token);
		token = next;
	}
	*list = NULL;
	free(list);
	list = NULL;
}
