/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:39:56 by jnenczak          #+#    #+#             */
/*   Updated: 2024/12/10 20:31:15 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

/**
 * Initializes a new token list.
 *
 * @return A pointer to the newly created token list.
 */
t_token_list	*init_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

/**
 * @brief Frees the memory allocated for a token list.
 *
 * This function frees the memory allocated for each token in the token list,
 * as well as the memory allocated for the token list itself.
 *
 * @param list The token list to be freed.
 */
void	free_token_list(t_token_list *list)
{
	t_token_node	*current;
	t_token_node	*next;

	if (list == NULL)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_token(current->token);
		free(current);
		current = next;
	}
	free(list);
}

void	print_token_list(t_token_list *list)
{
	t_token_node	*current;
	size_t			i;

	if (list == NULL)
		return ;
	current = list->head;
	while (current != NULL)
	{
		printf("Token: [%s]", get_token_description(current->token->type));
		if (current->token->value != NULL)
		{
			printf(" (%s)\n", current->token->value);
			if (current->token->args != NULL)
			{
				i = -1;
				while (current->token->args[++i])
					printf("	- ARG: %s\n", current->token->args[i]);
			}
		}
		else
			printf("\n");
		current = current->next;
	}
}

/**
 * Adds a token to the token list.
 *
 * @param list The token list to add the token to.
 * @param token The token to be added.
 */
void	add_token(t_token_list *list, t_token *token)
{
	t_token_node	*node;

	node = malloc(sizeof(t_token_node));
	node->token = token;
	node->next = NULL;
	node->prev = NULL;
	if (list->tail)
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	else
	{
		list->head = node;
		list->tail = node;
	}
}

size_t	token_list_size(t_token_list *list)
{
	t_token_node	*current;
	size_t			size;

	if (list == NULL)
		return (0);
	current = list->head;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_token_node	*get_token_at_index(t_token_list *list, int index)
{
	t_token_node	*current;
	int				i;

	if (list == NULL)
		return (NULL);
	current = list->head;
	i = 0;
	while (current != NULL)
	{
		if (i == index)
			return (current);
		i++;
		current = current->next;
	}
	return (NULL);
}