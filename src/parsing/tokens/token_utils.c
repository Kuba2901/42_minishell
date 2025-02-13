/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:06:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:07:27 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

static const char	*_token_type_to_string(t_token_type type)
{
	if (type == TOKEN_STRING)
		return ("TOKEN_STRING");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else
		return ("UNKNOWN_TOKEN");
}

/**
 * @brief Prints the details of a single token node and its arguments.
 *
 * This function iterates through a linked list of token nodes and prints the
 * type, command/file, and arguments of each token node. It uses the helper
 * function `_token_type_to_string` to convert the token type to a string for
 * printing.
 *
 * @param token A pointer to the first token node in the linked list.
 */
void	token_print(t_token_node *token)
{
	int	i;

	while (token)
	{
		printf("Token type: %s\n", _token_type_to_string(token->type));
		if (token->args)
		{
			i = -1;
			printf("Token command / file: %s\n", token->args[++i]);
			printf("Token args:\n");
			while (token->args[++i])
				printf("	-> %s\n", token->args[i]);
		}
		if (token->next)
			printf("\n\n");
		token = token->next;
	}
}

/**
 * @brief Prints the details of a list of token nodes.
 *
 * This function checks if the head of the token node list is valid and then
 * calls `token_print` to print the details of the token nodes.
 *
 * @param head A double pointer to the head of the token node list.
 */
void	token_list_print(t_token_node **head)
{
	if (!head || !*head)
		return ;
	token_print(*head);
}
