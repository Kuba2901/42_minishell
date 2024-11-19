/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:46 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/19 20:14:21 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

t_env_list	*env_list_init_populated(const char **envp)
{
	t_env_list	*ret;
	t_env_node	*node;

	ret = env_list_initialize();
	while (*envp++)
	{
		node = env_node_initialize(*envp);
		if (node != NULL)
			env_list_insert_node(ret, node);
		node = NULL;
	}
	return (ret);
}

t_env_list	*env_list_initialize(void)
{
	t_env_list	*ret;

	ret = malloc(sizeof(t_env_list));
	if (!ret)
	{
		log_error("Failed to allocate memory for t_env_list instance\n");
		return (NULL);
	}
	ret->head = NULL;
	ret->tail = NULL;
	return (ret);
}

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

void	_env_list_place_node(t_env_list *list, t_env_node *current, t_env_node *node)
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
				env_node_update(current, node->value);
			return ;
		}
		current = current->next;
	}
	_env_list_append_node(list, node);
}

t_env_node	*env_list_read_node(t_env_list *list, char *key)
{
	t_env_node	*current;

	if (!list || !list->head || !list->tail || !key)
	{
		log_error("[ENV_READ_NODE] Failed to read t_env_node");
		return (NULL);
	}
	current = list->head;
	while (current != NULL)
	{
		if (!env_node_comp(current, key))
			return (current);
		current = current->next;
	}
	log_error("[ENV_READ_NODE] Failed to read node - does not exist");
	return (NULL);
}

void	env_list_delete_node(t_env_list *list, char *key)
{
	t_env_node	*current;

	if (!list || !list->head || !list->tail || !key)
		return ;
	current = list->head;
	while (current != NULL)
	{
		if (env_node_comp(current, key))
		{
			env_node_delete(current);
			return ;
		}
		current = current->next;
	}
}

void	env_list_delete(t_env_list *list)
{
	t_env_node	*current;
	t_env_node	*temp;

	if (!list || !list->head || !list->tail)
	{
		log_error("[ENV_LIST_DELETE] Failed to delete t_env_list instance\n");
		return ;
	}
	current = list->head;
	while (current != NULL)
	{
		temp = current->next;
		env_node_delete(current);
		current = temp;
	}
	current = NULL;
	temp = NULL;
	free(list);
	list = NULL;
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