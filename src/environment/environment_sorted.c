/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:18:14 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 20:57:19 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

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
