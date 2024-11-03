/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:26:32 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 18:27:32 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

/**
 * @brief Handles a word in the tokenization process.
 *
 * This function takes a pointer to the current character and a token list.
 * It iterates through the characters starting from the current position until it reaches
 * the end of the string or encounters a whitespace character, a special character
 * ('&', '|', '(', ')', '<', '>'), or a null character ('\0').
 * It then adds a token of type TOKEN_WORD to the token list, containing the substring
 * from the start position to the current position.
 *
 * @param current A pointer to the current character.
 * @param list The token list to add the token to.
 */
void	handle_word(const char **current, t_token_list *list)
{
	const char	*start;

	start = *current;
	while (**current != '\0' && !ft_is_whitespace(**current) \
		&& !ft_strchr("&|()<>", **current))
		(*current)++;
	add_token(list, create_token(TOKEN_WORD,
			ft_substr(start, 0, *current - start)));
}

/**
 * @brief Handles logical operators in the tokenization process.
 *
 * This function checks the current character and adds the corresponding token to the token list.
 * If the current character is '&' and the next character is also '&', it adds a TOKEN_AND to the list.
 * If the current character is '|' and the next character is also '|', it adds a TOKEN_OR to the list.
 *
 * @param current A pointer to the current character in the input string.
 * @param list A pointer to the token list.
 */
void	handle_logical(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '&' && *(cur + 1) == '&')
	{
		add_token(list, create_token(TOKEN_AND, NULL));
		(*current) += 2;
	}
	else if (*cur == '|' && *(cur + 1) == '|')
	{
		add_token(list, create_token(TOKEN_OR, NULL));
		(*current) += 2;
	}
}
