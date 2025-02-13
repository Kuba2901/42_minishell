/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:08:19 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 15:14:41 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

void	token_append(t_token_node **list, t_token_node *new_node)
{
	t_token_node	*last_node;

	if (!new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last_node = *list;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
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
void	handle_simple_tokens(char **current, t_token_node **list)
{
	char	*cur;

	cur = *current;
	if (*cur == '|')
	{
		token_append(list, token_create(TOKEN_PIPE, NULL));
		(*current)++;
	}
	else if (*cur == '<' || *cur == '>')
		handle_arrows(list, current);
}

/**
 * @brief Handles quoted tokens.
 *
 * This function is responsible for handling quoted tokens
 * in the tokenisation process.
 * It takes a pointer to the current character, a token list,
 * and the type of quote.
 * It searches for the closing quote and creates a token with
 * the quoted content.
 * If the closing quote is missing, it prints an error message.
 *
 * @param current A pointer to the current character.
 * @param list The token list to add the created token to.
 * @param type The type of quote.
 */
void	handle_quoted(char **current, t_token_node **list, char type)
{
	char	*start;
	char	*str;

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
	str = ft_substr(start, 0, *current - start);
	token_append(list, token_create(TOKEN_STRING, str));
	free(str);
}

/**
 * @brief Handles a word in the tokenization process.
 *
 * This function takes a pointer to the current character
 * and a token list.
 * It iterates through the characters starting from the
 * current position until it reaches
 * the end of the string or encounters a whitespace character,
 * a special character
 * ('&', '|', '(', ')', '<', '>'), or a null character ('\0').
 * It then adds a token of type TOKEN_WORD to the token list,
 * containing the substring
 * from the start position to the current position.
 *
 * @param current A pointer to the current character.
 * @param list The token list to add the token to.
 */
void	handle_word(t_token_node **list, char **current)
{
	char	*start;
	char	*str;
	t_bool	is_env_var_set;

	start = *current;
	is_env_var_set = false;
	while (**current != '\0' && !ft_is_whitespace(**current) \
		&& !ft_strchr("&|()", **current) && !is_env_var_set)
	{
		if (**current == '=')
			is_env_var_set = true;
		(*current)++;
	}
	str = ft_substr(start, 0, *current - start);
	token_append(list, token_create(TOKEN_STRING, str));
	free(str);
}
