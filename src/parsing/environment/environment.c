/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:54:45 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/18 18:21:52 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

t_env_list  *init_list(void)
{
	t_env_list  *ret;

	ret = malloc(sizeof(t_env_list));
	if (!ret)
	{
		printf("Error: failed to allocate memory for the env arguments list.\n");
		return (NULL);
	}
	ret->head = NULL;
	ret->tail = NULL;
	return (ret);
}

t_env_node	*init_node(const char *key, const char *value)
{
	t_env_node	*ret;

	ret = malloc(sizeof(t_env_node));
	if (!ret)
	{
		printf("Error: failed to allocate memory for an env node\n");
		return (ret);
	}
	ret->next = NULL;
	ret->prev = NULL;
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	return (ret);
}

// POTENTIAL-BUG: Verify whether getting rid of all double quotes is safe


static int comp_nodes(t_env_node *n1, t_env_node *n2)
{
	size_t	comp_size;
	size_t	n1_key_len;
	size_t	n2_key_len;

	if (!n1 || !n2 || !n1->key || !n2->key)
		return (-1);
	n1_key_len = ft_strlen(n1->key);
	n2_key_len = ft_strlen(n2->key);
	if (n1_key_len > n2_key_len)
		comp_size = n1_key_len;
	else
		comp_size = n2_key_len;
	return (ft_strncmp(n2->key, n1->key, comp_size));
}

void	delete_env_node(t_env_list *list, char *key)
{
	t_env_node	*current;
	size_t		key_len;
	size_t		curr_key_len;

	if (!list || !list->head || !list->tail || !key)
		return ;
	current = list->head;
	key_len = ft_strlen(key);
	while (current)
	{
		curr_key_len = ft_strlen(current->key);
		if (key_len == curr_key_len) // 1. Check if the keys are of the same length - if yes - compare, else - proceed to the next one 
		{
			if (!ft_strncmp(current->key, key, key_len)) // 2. Compare the keys - if they have the same value, free the variables and relink the nodes around
			{
				if (current->prev)
					current->prev->next = current->next;
				if (current->next)
					current->next->prev = current->prev;
				free(current->key);
				free(current->value);
				free(current);
				current = NULL;
				printf("\033[32mSuccess: node deleted.\033[0m\n");
				return ;
			}
		}
		current = current->next;
	}
	log_error("Error: (delete) node for the key was not found.");
}

static void	insert_node_to_list(t_env_list *list, t_env_node *node)
{
	t_env_node	*current;
	int			comp_res;

	if (!list || !node)
		return ;
	if (list->head == NULL && list->tail == NULL)
	{
		list->head = node;
		list->tail = node;
		return ;
	}
	current = list->head;
	while (current != NULL)
	{
		if (current->next == NULL) // 4. There are no more nodes - break and append to the end
			break ;
		comp_res = comp_nodes(current, node);
		if (comp_res < 0) // 2. The current is lower - insert before and relink the nodes
		{
			// RELINK NODE
			node->next = current;
			node->prev = current->prev;

			// RELINK CURRENT
			if (current->prev)
				current->prev->next = node;
			else
				list->head = node;
			current->prev = node;
			return ;
		}
		else if (!comp_res) // 3. The current node has the same key - change the value
		{
			current->value = node->value;
			return ;
		}
		current = current->next;
	}
	// 4a. Append to the end of the list
	list->tail = node;
	current->next = node;
	node->prev = current;
}

void	free_env_list(t_env_list *list)
{
	t_env_node	*current;
	t_env_node	*temp;

	if (!list || !list->head)
	{
		log_error("Error: list is null or list->head is null\n");
		return ;
	}
	current = list->head;
	while (current)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	current = NULL;
}

t_env_list	*create_env_list(const char **envp)
{
	t_env_list	*env_list;
	int			i;

	env_list = init_list();
	if (!env_list)
	{
		log_error("Error: failed to initialise the env list\n");
		return (NULL);
	}
	i = -1;
	while (envp[++i])
		insert_node_to_list(env_list, create_node(envp[i]));
	return (env_list);
}



void	insert_env_node(const char *entry, t_env_list *list)
{
	t_env_node	*node;

	node = create_node(entry);
	if (!node)
	{
		log_error("Error: failed to create a new env node\n");
		return ;
	}
	insert_node_to_list(list, node);
	log_success("Success: the node has been successfully added to the list\n");
}
