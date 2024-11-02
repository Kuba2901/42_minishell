/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:39:56 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 19:40:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

t_token_list	*init_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

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

	if (list == NULL)
		return ;
	current = list->head;
	while (current != NULL)
	{
		printf("Token: (%d)", current->token->type);
		if (current->token->value != NULL)
			printf(" (%s)\n", current->token->value);
		else
			printf("\n");
		current = current->next;
	}
}

void	add_token(t_token_list *list, t_token *token)
{
	t_token_node	*node;

	node = malloc(sizeof(t_token_node));
	node->token = token;
	node->next = NULL;
	if (list->tail)
	{
		list->tail->next = node;
		list->tail = node;
	}
	else
	{
		list->head = node;
		list->tail = node;
	}
}
