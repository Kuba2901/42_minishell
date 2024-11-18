/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:21:03 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/18 18:24:50 by jnenczak         ###   ########.fr       */
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