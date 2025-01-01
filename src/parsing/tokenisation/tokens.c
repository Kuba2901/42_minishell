/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:32:21 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/10 20:31:55 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

static void	tok_assign_args(t_token_node *src)
{
	size_t			i;
	t_token_node	*temp;
	t_token_node	*next;

	i = 0;
	temp = src->next;
	while (temp != NULL)
	{
		if (src->token->type == temp->token->type \
			&& src->token->type == TOKEN_WORD)
		{
			i++;
			temp = temp->next;
		}
		else
			break ;
	}
	if (!i)
		return ;
	src->token->args = malloc(sizeof(char *) * (i + 1));
	if (!src->token->args)
		return ;
	i = 0;
	temp = src->next;
	while (temp != NULL)
	{
		if (src->token->type == temp->token->type \
			&& src->token->type == TOKEN_WORD)
		{
			src->token->args[i] = ft_strdup(temp->token->value);
			next = temp->next;
			free_token(temp->token);
			free(temp);
			i++;
			temp = next;
		}
		else
			break ;
	}
	src->token->args[i] = NULL;
	// i = -1;
	// while (src->token->args[++i])
	// 	printf("ARG: %s\n", src->token->args[i]);
	src->next = temp;
}

/**
 * @brief Joins consecutive word tokens in the given token list.
 * 
 * This function iterates through the token list and checks for consecutive word tokens.
 * If two consecutive word tokens are found, they are joined together by appending the value
 * of the second token to the value of the first token, separated by a space.
 * The second token is then removed from the list.
 * 
 * @param src The token list to be processed.
 */
static void	ft_join_tokens(t_token_list *src)
{
	t_token_node	*node1;

	if (src == NULL || src->head == NULL)
		return ;
	node1 = src->head;
	while (node1 != NULL)
	{
		tok_assign_args(node1);
		node1 = node1->next;
	}
}

/**
 * Tokenizes the given input string.
 *
 * @param input The input string to be tokenized.
 * @return A pointer to the token list.
 */
t_token_list	*ft_tokenize(const char *input)
{
	const char		*current;
	t_token_list	*list;

	current = input;
	list = init_token_list();
	while (*current != '\0')
	{
		while (*current && ft_is_whitespace(*current))
			current++;
		if ((*current == '&' && *(current + 1) == '&') \
			|| (*current == '|' && *(current + 1) == '|'))
			handle_logical(&current, list);
		else if (ft_strchr("()|<>", *current))
			handle_simple_tokens(&current, list);
		else if (*current == '"' || *current == '\'')
			handle_quoted(&current, list, *current);
		else
			handle_word(&current, list);
	}
	ft_join_tokens(list);
	return (list);
}
