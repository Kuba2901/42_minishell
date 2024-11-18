/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:15:19 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/18 18:23:34 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

static t_env_node	*_env_node_initialize(char *key, char *value)
{
	t_env_node	*ret;

	ret = malloc(sizeof(t_env_node));
	if (!ret)
	{
		log_error("[ENV_CREATE_NODE] Failed to allocate memory for t_env_node\n");
		return (NULL);
	}
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

t_env_node	*env_node_initialize(const char *entry)
{
	t_env_node	*ret;
	char		**params;
	char		*trimmed_entry;
	int			i;

	trimmed_entry = trim_double_quotes(entry);
	params = ft_split(trimmed_entry, '=');
	free(trimmed_entry);
	if (!params || !params[0] || !params[1] || params[2])
	{
		log_warning("Warning: failed to parse the env entry using ft_split... ignoring");
		return (NULL);
	}
	ret = _env_node_initialize(params[0], params[1]);
	i = -1;
	while (params[++i])
		free(params[i]);
	free(params);
	params = NULL;
	return (ret);
}

char	*env_node_read(t_env_node *node)
{
	if (!node || !node->value)
	{
		log_error("[ENV_NODE_READ] Failed to read node value");
		return (NULL);
	}
	return (node->value);
}

void	env_node_update(t_env_node *node, char *value)
{
	if (!node)
		return ;
	if (!value)
		return ;
	if (node->value)
		free(node->value);
	node->value = ft_strdup(value);
	if (!node->value)
		log_error("[_ENV_UPDATE_NODE] Failed to update node value");
}

static void	env_node_delete(t_env_node	*node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	node = NULL;
}