/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:05:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:41:10 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

/**
 * @brief Clears the current arguments of a token node.
 *
 * This function frees all the strings in the `args` array of the given
 * token node and sets each pointer to NULL. It also frees the `args`
 * array itself and sets the pointer to NULL.
 *
 * @param src Pointer to the token node whose arguments are to be cleared.
 */
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

/**
 * @brief Assigns arguments from source token node to a new arguments array.
 *
 * This function iterates through the linked list of token nodes starting from
 * the node pointed to by `temp`. If the type of the current token node matches
 * the type of the source token node (`src`) and the type is `TOKEN_STRING`,
 * it duplicates the argument string from the current token node and assigns it
 * to the new arguments array (`new_args`) at index `i`. The current token node
 * is then deleted, and the function moves to the next token node in the list.
 * The process continues until a token node with a different type is encountered
 * or the end of the list is reached. The new arguments array is terminated with
 * a NULL pointer.
 *
 * @param temp Pointer to the pointer of the current token node in the linked list.
 * @param src Pointer to the source token node whose type is used for comparison.
 * @param new_args Array of strings where the duplicated arguments will be stored.
 * @param i Index in the new arguments array where the next duplicated argument will be stored.
 */
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

/**
 * @brief Assigns arguments to a token node.
 *
 * This function assigns arguments to a token node by first counting the number
 * of arguments, allocating memory for the new arguments, and then copying the
 * arguments from the source token node to the new arguments array. It also clears
 * the current arguments of the source token node and updates the source token node
 * with the new arguments and the next token node.
 *
 * @param src Pointer to the source token node.
 */
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

/**
 * @brief Joins tokens in the provided token list.
 *
 * This function iterates through the given token list and assigns arguments
 * to each token node using the _tok_assign_args function.
 *
 * @param list A double pointer to the head of the token list.
 *             If the list is NULL or the head of the list is NULL, the function returns immediately.
 */
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
