/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:21:03 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/19 19:45:56 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

char	*env_node_trim_double_quotes(const char *str)
{
	char	*new_str;
	size_t	i, j;

	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	env_node_comp(t_env_node *n1, char *key)
{
	size_t	comp_size;
	size_t	n1_key_len;
	size_t	n2_key_len;

	if (!n1 || !n1->key || !key)
		return (-1);
	n1_key_len = ft_strlen(n1->key);
	n2_key_len = ft_strlen(key);
	if (n1_key_len > n2_key_len)
		comp_size = n1_key_len;
	else
		comp_size = n2_key_len;
	return (ft_strncmp(key, n1->key, comp_size));
}


void	env_list_print(t_env_list *list)
{
	t_env_node	*node;
	
	if (!list || !list->head)
	{
		log_error("Error: env list is NULL or env list->head is NULL\n");
	}
	node = list->head;
	printf("---- PRINTING ENV NODES ----\n");
	while (node)
	{
		printf("%s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
}