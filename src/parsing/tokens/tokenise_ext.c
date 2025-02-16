/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:18:55 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:40:06 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

/**
 * @brief Counts the number of consecutive tokens of the same type as the source token.
 *
 * This function iterates through the linked list of tokens starting from the next token
 * of the given source token (`src`). It counts how many consecutive tokens have the same
 * type as the source token and are of type `TOKEN_STRING`.
 *
 * @param src A pointer to the source token node from which to start counting.
 * @return The number of consecutive tokens of the same type as the source token.
 */
size_t	token_count_args(t_token_node *src)
{
	size_t			i;
	t_token_node	*temp;

	i = 0;
	temp = src->next;
	while (temp != NULL)
	{
		if (src->type == temp->type \
			&& src->type == TOKEN_STRING)
		{
			i++;
			temp = temp->next;
		}
		else
			break ;
	}
	return (i);
}
