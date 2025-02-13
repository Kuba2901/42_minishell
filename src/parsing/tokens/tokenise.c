/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:05:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 15:03:57 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

static void	_tok_clear_current_args(t_token_node *src)
{
	int	i;

	i = -1;
	while (src->args[++i])
	{
		free(src->args[i]);
		src->args[i] = NULL;
	}
	free(src->args);
	src->args = NULL;
}

static void	_tok_assign_args_ext(t_token_node **temp, t_token_node *src,
		char **new_args, size_t i)
{
	t_token_node	*next;

	while (*temp != NULL)
	{
		if (src->type == (*temp)->type \
			&& src->type == TOKEN_STRING)
		{
			new_args[i] = ft_strdup((*temp)->args[0]);
			next = (*temp)->next;
			token_delete(*temp);
			i++;
			*temp = next;
		}
		else
			break ;
	}
	new_args[i] = NULL;
}

static void	_tok_assign_args(t_token_node *src)
{
	size_t			i;
	t_token_node	*temp;
	char			**new_args;

	i = token_count_args(src);
	if (!i)
		return ;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	temp = src->next;
	new_args[i] = ft_strdup(src->args[i]);
	_tok_clear_current_args(src);
	i++;
	_tok_assign_args_ext(&temp, src, new_args, i);
	src->args = new_args;
	src->next = temp;
}

static void	_join_tokens(t_token_node	**list)
{
	t_token_node	*node1;

	if (list == NULL || *list == NULL)
		return ;
	node1 = *list;
	while (node1 != NULL)
	{
		_tok_assign_args(node1);
		node1 = node1->next;
	}
}

/**
 * tokenise - Tokenizes the input string into a list of tokens.
 * @input: The input string to be tokenized.
 *
 * This function takes an input string and tokenizes it into a list of tokens.
 * It handles different types of tokens including 
 * simple tokens (like '(', ')', '|', '<', '>'),
 * quoted strings, and words. The function skips over
 * whitespace and processes each token
 * accordingly. The resulting list of tokens is returned.
 *
 * @returns: A pointer to the list of tokens, or NULL if memory allocation fails.
 */
t_token_node	**tokenise(char *input)
{
	char			*current;
	t_token_node	**list;

	list = malloc(sizeof(t_token_node *));
	if (!list)
		return (NULL);
	*list = NULL;
	current = input;
	while (*current)
	{
		while (*current && ft_is_whitespace(*current))
			current++;
		if (ft_strchr("()|<>", *current))
			handle_simple_tokens(&current, list);
		else if (*current == '"' || *current == '\'')
			handle_quoted(&current, list, *current);
		else
			handle_word(list, &current);
	}
	_join_tokens(list);
	return (list);
}
