/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:46 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/19 20:16:31 by jnenczak         ###   ########.fr       */
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

t_env_node	*env_list_read_node(t_env_list *list, char *key)
{
	t_env_node	*current;

	if (!list || !list->head || !list->tail || !key)
	{
		// log_error("[ENV_READ_NODE] Failed to read t_env_node");
		return (NULL);
	}
	current = list->head;
	while (current != NULL)
	{
		if (!env_node_comp(current, key))
			return (current);
		current = current->next;
	}
	// log_error("[ENV_READ_NODE] Failed to read node - does not exist");
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
