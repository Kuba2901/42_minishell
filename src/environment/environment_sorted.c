/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:18:14 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:30:02 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Copies a given environment node.
 *
 * This function creates a new environment node and copies the key, value, 
 * and is_private fields from the given node to the new node. The next 
 * pointer of the new node is set to NULL.
 *
 * @param node The environment node to be copied.
 * @return A pointer to the newly created environment node, or NULL if 
 * memory allocation fails.
 */
static t_environment_node	*_copy_node(t_environment_node *node)
{
	t_environment_node	*new_node;

	new_node = malloc(sizeof(t_environment_node));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(node->key);
	new_node->value = ft_strdup(node->value);
	new_node->is_private = node->is_private;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Inserts a copy of the given node at the beginning of the list.
 *
 * This function creates a copy of the provided node and inserts it at the 
 * beginning of the list pointed to by `ret`. If the copy operation is 
 * successful, the new node is linked as the first node in the list.
 *
 * @param ret A pointer to the head of the list where the new node will be inserted.
 * @param current The node to be copied and inserted at the beginning of the list.
 */
static void	_insert_at_beginning(t_environment_node **ret,
		t_environment_node *current)
{
	t_environment_node	*new_node;

	new_node = _copy_node(current);
	if (new_node)
	{
		new_node->next = *ret;
		*ret = new_node;
	}
}

/**
 * @brief Inserts a node in the middle of a sorted linked list.
 *
 * This function inserts a new node into a sorted linked list in its correct
 * position based on the key comparison. It traverses the list until it finds
 * the appropriate position for the new node and then inserts it.
 *
 * @param temp Pointer to the current node in the list where the insertion
 *             should start.
 * @param current Pointer to the node that needs to be inserted into the list.
 */
static void	_insert_in_middle(t_environment_node *temp,
		t_environment_node *current)
{
	t_environment_node	*new_node;

	while (temp->next && ft_strcmp(current->key, temp->next->key) > 0)
		temp = temp->next;
	new_node = _copy_node(current);
	if (new_node)
	{
		new_node->next = temp->next;
		temp->next = new_node;
	}
}

/**
 * @brief Creates a sorted copy of the environment list.
 *
 * This function takes an unsorted linked list of environment variables and 
 * returns a new linked list that is sorted by the keys of the environment 
 * variables. The original list remains unchanged.
 *
 * @param original A pointer to the head of the original unsorted environment 
 * list.
 * @return A pointer to the head of the new sorted environment list.
 */
t_environment_node	*environment_list_get_sorted_copy(
		t_environment_node *original)
{
	t_environment_node	*current;
	t_environment_node	*temp;
	t_environment_node	*ret;

	ret = NULL;
	current = original;
	while (current)
	{
		if (!ret)
			ret = _copy_node(current);
		else
		{
			temp = ret;
			if (ft_strcmp(current->key, temp->key) < 0)
				_insert_at_beginning(&ret, current);
			else
				_insert_in_middle(temp, current);
		}
		current = current->next;
	}
	return (ret);
}
