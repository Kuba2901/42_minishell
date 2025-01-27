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
		// log_error("[ENV_VALUE_READ] Failed to read node value");
		return (NULL);
	}
	return (node->value);
}

static char	*_trim_double_quotes(char *str)
{
	char	*ret;

	ret = malloc((ft_strlen(str) - 1) * sizeof(char));
	str++;
	ft_strlcpy(ret, str, ft_strlen(str));
	return (ret);
}

static char	*_expand_multiple_variables(t_env_list *list, char *str)
{
	char	*trimmed;
	char	*ret;
	char	**split;
	int		i;

	trimmed = _trim_double_quotes(str);
	split = ft_split(trimmed, ' ');
	ret = ft_strdup("");
	i = -1;
	while (split[++i])
	{
		ret = ft_join_reassign(ret, env_value_expand(list, split[i]));
		ret = ft_join_reassign(ret, ft_strdup(" "));
	}
	return (ret);
}

char	*env_value_expand(t_env_list *list, char *key)
{
	t_env_node	*node;
	size_t		is_double_quoted;
	// char		*trimmed_key;

	is_double_quoted = 0;
	if (key[0] == '$')
	{
		printf("First char is $, skipping 1. New key: %s\n", key + 1);
		key++;
	}
	else if (key[0] == '"')
		is_double_quoted = 1;
	else
		return (key);
	if (is_double_quoted)
	{
		// TODO: Implement multi env variable scenario
		return (_expand_multiple_variables(list, key));
	}
	else
		node = env_list_read_node(list, key);
	if (!node)
		return (NULL);
	return (node->value);
}