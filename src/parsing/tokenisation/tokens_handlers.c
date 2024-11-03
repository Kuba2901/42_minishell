/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:37:40 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 18:06:49 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

static void	handle_arrows_left(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*(cur + 1) == '<')
	{
		add_token(list, create_token(TOKEN_HEREDOC, NULL));
		(*current) += 2;
	}
	else
	{
		add_token(list, create_token(TOKEN_REDIRECT_IN, NULL));
		(*current)++;
	}
}

static void	handle_arrows_right(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*(cur + 1) == '>')
	{
		add_token(list, create_token(TOKEN_APPEND, NULL));
		(*current) += 2;
	}
	else
	{
		add_token(list, create_token(TOKEN_REDIRECT_OUT, NULL));
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
void	handle_arrows(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '<')
		handle_arrows_left(current, list);
	else if (*cur == '>')
		handle_arrows_right(current, list);
}

/**
 * @brief Handles simple tokens in the input string.
 *
 * This function takes a pointer to the current character in the input string
 * and a pointer to a token list. It checks the current character and adds the
 * corresponding token to the token list. The current character pointer is
 * updated accordingly.
 *
 * @param current Pointer to the current character in the input string.
 * @param list Pointer to the token list.
 */
void	handle_simple_tokens(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '(')
	{
		add_token(list, create_token(TOKEN_LPAREN, NULL));
		(*current)++;
	}
	else if (*cur == ')')
	{
		add_token(list, create_token(TOKEN_RPAREN, NULL));
		(*current)++;
	}
	else if (*cur == '|')
	{
		add_token(list, create_token(TOKEN_PIPE, NULL));
		(*current)++;
	}
	else if (*cur == '<' || *cur == '>')
		handle_arrows(current, list);
}

/**
 * @brief Handles quoted tokens.
 *
 * This function is responsible for handling quoted tokens in the tokenisation process.
 * It takes a pointer to the current character, a token list, and the type of quote.
 * It searches for the closing quote and creates a token with the quoted content.
 * If the closing quote is missing, it prints an error message.
 *
 * @param current A pointer to the current character.
 * @param list The token list to add the created token to.
 * @param type The type of quote.
 */
void	handle_quoted(const char **current, t_token_list *list, char type)
{
	const char	*start;

	start = *current;
	(*current)++;
	while (**current != '\0' && **current != type)
		(*current)++;
	if (**current == '\0')
	{
		fprintf(stderr, "Error: missing closing quote\n");
		return ;
	}
	(*current)++;
	add_token(list, create_token(TOKEN_WORD,
			ft_substr(start, 0, *current - start)));
}
