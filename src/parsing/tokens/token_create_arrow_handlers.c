/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create_arrow_handlers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:04:54 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:35:59 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

/**
 * @brief Handles the creation of tokens for left arrow ('<') characters.
 *
 * This function processes the current character in the input string to determine
 * if it represents a single left arrow ('<') or a double left arrow ('<<'). It then
 * creates the appropriate token and appends it to the token list.
 *
 * @param list A pointer to the list of token nodes.
 * @param current A pointer to the current position in the input string.
 */
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

/**
 * @brief Handles the creation of right arrow tokens (">" and ">>").
 *
 * This function checks the current character and the next character to determine
 * if it is a single right arrow (">") or a double right arrow (">>"). It then
 * creates the appropriate token and appends it to the token list.
 *
 * @param list A pointer to the list of token nodes.
 * @param current A pointer to the current character pointer in the input string.
 */
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
