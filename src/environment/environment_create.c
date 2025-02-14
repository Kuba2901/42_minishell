/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:20:21 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 22:17:57 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

static void	_environment_node_simple_delete(t_environment_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

/**
 * @brief Inserts a new node into the environment list.
 * 
 * This function adds a new node to the beginning of an environment
 * list if it's empty. If not, it
 * traverses the list looking for a node with the same key as the 
 * one being inserted. If found, it updates
 * the value and frees resources. Otherwise, it appends the 
 * new node to the end.
 * 
 * @param head A double pointer to the head of the environment list.
 * @param node The node to be inserted or updated.
 */
static void	_environment_node_insert(t_environment_node **head,
		t_environment_node *node)
{
	t_environment_node	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, node->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(node->value);
			tmp->is_private = node->is_private;
			_environment_node_simple_delete(node);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = node;
}

/**
 * @brief Creates an environment node from an entry string and 
 * adds it to the shell's environment list.
 * 
 * This function uses environment_node_from_entry to parse the entry string 
 * into a node. If successful, it inserts
 * this node into the shell's environment list using 
 * _environment_node_insert. It returns the created node,
 * or NULL if parsing fails.
 * 
 * @param entry The entry string to process.
 * @param shell A pointer to the shell context containing 
 * the environment list.
 * @return t_environment_node* A pointer to the newly created 
 * and inserted node, or NULL.
 */
t_environment_node	*enviroment_node_create(const char *entry, t_shell *shell,
		t_bool is_private)
{
	t_environment_node	*node;

	if (!entry || !shell)
		return (NULL);
	node = environment_node_from_entry(entry, is_private);
	if (node != NULL)
		_environment_node_insert(&shell->env, node);
	return (node);
}

/**
 * @brief Initializes an environment list from an array of 
 * environment variable strings.
 * 
 * This function processes each string in the provided array 
 * using environment_node_from_entry to create nodes.
 * Each valid node is inserted into the environment list. It returns 
 * the head of the newly created list,
 * which may be empty if all entries are invalid.
 * 
 * @param envp An array of strings representing environment variables.
 * @return t_environment_node* The head of the environment list, 
 * or NULL if no nodes were created.
 */
t_environment_node	*environment_list_initialize(const char **envp)
{
	t_environment_node	*head;
	t_environment_node	*node;

	head = NULL;
	while (*envp)
	{
		node = environment_node_from_entry(*envp, false);
		if (node != NULL)
			_environment_node_insert(&head, node);
		envp++;
	}
	return (head);
}
