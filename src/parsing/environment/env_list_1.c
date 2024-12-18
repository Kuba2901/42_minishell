/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:15:31 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/19 20:18:02 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

void	_env_list_append_node(t_env_list *list, t_env_node *node)
{
	list->tail->next = node;
	node->prev = list->tail;
	list->tail = node;
}

int	_env_list_add_head(t_env_list *list, t_env_node *node)
{
	if (list->head == NULL && list->tail == NULL)
	{
		list->head = node;
		list->tail = node;
		return (1);
	}
	return (0);
}

void	_env_list_place_node(t_env_list *list, t_env_node *current,
	t_env_node *node)
{
	node->next = current;
	node->prev = current->prev;
	if (current->prev)
		current->prev->next = node;
	else
		list->head = node;
	current->prev = node;
}

void	env_list_insert_node(t_env_list *list, t_env_node *node)
{
	t_env_node	*current;
	int			comp_res;

	if (!list || !node)
		return ;
	if (_env_list_add_head(list, node))
		return ;
	current = list->head;
	while (current != NULL)
	{
		if (current->next == NULL)
			break ;
		comp_res = env_node_comp(current, node->key);
		if (comp_res <= 0)
		{
			if (comp_res < 0)
				_env_list_place_node(list, current, node);
			else
				env_node_update(current, node);
			return ;
		}
		current = current->next;
	}
	_env_list_append_node(list, node);
}

void	env_list_insert(t_env_list *list, const char *entry)
{
	t_env_node	*node;

	if (!list || !entry)
	{
		log_error("[ENV_LIST_INSERT] Failed to initialize a new node.");
		return ;
	}
	node = env_node_initialize(entry);
	if (!node)
	{
		log_error("[ENV_LIST_INSERT] Failed to initialize a new node.");
		return ;
	}
	env_list_insert_node(list, node);
}

char	*env_value_read(t_env_list *list, char *key)
{
	t_env_node	*node;

	node = env_list_read_node(list, key);
	if (!node)
	{
		log_error("[ENV_VALUE_READ] Failed to read node value");
		return (NULL);
	}
	return (node->value);
}
