/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:28 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 15:41:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Frees memory associated with an environment node
 * and sets the pointer to NULL.
 * 
 * This function performs cleanup of a 
 * t_environment_node by freeing its key, value,
 * and the node itself. It ensures that all resources 
 * are properly released and
 * the pointer is set to NULL to prevent
 *  dangling pointers.
 * 
 * @param node A double pointer to the environment 
 * node to be deleted.
 */
static void	_environment_node_delete(t_environment_node **node)
{
	if (!node || !*node)
		return ;
	free((*node)->key);
	free((*node)->value);
	free(*node);
	*node = NULL;
}

/**
 * @brief Deletes an environment node with a specified 
 * key from the shell's environment list.
 * 
 * This function searches for a node with the given key in 
 * the shell's environment list.
 * If found, it removes the node from the list and frees 
 * its resources. If not found,
 * or if inputs are invalid, it does nothing.
 * 
 * @param key The key of the node to delete.
 * @param shell A pointer to the shell context containing 
 * the environment list.
 */
void	enviroment_node_delete(const char *key, t_shell *shell)
{
	t_environment_node	*tmp;
	t_environment_node	*prev;
	t_environment_node	**env;

	env = &shell->env;
	if (!env || !*env || !key)
		return ;
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			_environment_node_delete(&tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/**
 * @brief Clears all nodes in the shell's environment list.
 * 
 * This function iterates through each node in the 
 * environment list, deletes them
 * one by one using _environment_node_delete, and updates 
 * the head pointer to NULL.
 * It ensures that all resources are properly freed and the 
 * list is completely cleared.
 * 
 * @param shell A pointer to the shell context containing 
 * the environment list.
 */
void	environment_list_clear(t_shell *shell)
{
	t_environment_node	**env;
	t_environment_node	*tmp;

	env = &shell->env;
	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		_environment_node_delete(env);
		*env = tmp;
	}
}
