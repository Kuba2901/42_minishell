/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:46 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/18 18:28:04 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

t_env_list	*env_list_init_populated(const char **envp)
{
	
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

void	env_list_insert_node(t_env_list *list, t_env_node *node)
{
	t_env_node	*current;
	int			comp_res;

	if (!list || !node)
		return (ENV_ERROR);
	if (list->head == NULL && list->tail == NULL)
	{
		list->head = node;
		list->tail = node;
		return (ENV_ERROR);
	}
	current = list->head;
	while (current != NULL)
	{
		if (current->next == NULL)
			break ;
		comp_res = env_comp_key_node(current, node->key);
		if (comp_res < 0)
		{
			node->next = current;
			node->prev = current->prev;
			if (current->prev)
				current->prev->next = node;
			else
				list->head = node;
			current->prev = node;
			return (ENV_INSERTED);
		}
		else if (!comp_res)
		{
			env_node_update(current, node->value);
			env_node_delete(node);
			return (ENV_UPDATED);
		}
		current = current->next;
	}
	list->tail = node;
	current->next = node;
	node->prev = current;
	return (ENV_INSERTED);
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
		if (!env_comp_key_node(current, key))
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
		if (env_comp_key_node(current, key))
		{
			_env_delete_node(current);
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