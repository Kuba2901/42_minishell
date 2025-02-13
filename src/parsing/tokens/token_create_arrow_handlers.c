/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create_arrow_handlers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:04:54 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:05:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

static void	handle_arrows_left(t_token_node **list, char **current)
{
	char	*cur;

	cur = *current;
	if (*(cur + 1) == '<')
	{
		token_append(list, token_create(TOKEN_HEREDOC, NULL));
		(*current) += 2;
	}
	else
	{
		token_append(list, token_create(TOKEN_REDIRECT_IN, NULL));
		(*current)++;
	}
}

static void	handle_arrows_right(t_token_node **list, char **current)
{
	char	*cur;

	cur = *current;
	if (*(cur + 1) == '>')
	{
		token_append(list, token_create(TOKEN_APPEND, NULL));
		(*current) += 2;
	}
	else
	{
		token_append(list, token_create(TOKEN_REDIRECT_OUT, NULL));
		(*current)++;
	}
}

/**
 * @brief Handles the arrows in the input string.
 *
 * This function determines whether the current character is '<' or '>'.
 * If it is '<', it calls the handle_arrows_left() function.
 * If it is '>', it calls the handle_arrows_right() function.
 *
 * @param current The current character in the input string.
 * @param list The token list to be updated.
 */
void	handle_arrows(t_token_node **list, char **current)
{
	char	*cur;

	cur = *current;
	if (*cur == '<')
		handle_arrows_left(list, current);
	else if (*cur == '>')
		handle_arrows_right(list, current);
}
