/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_create_ext.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:23:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 22:36:47 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>

/**
 * @brief Trims double quotes from both ends of the input string.
 * 
 * This function removes leading and trailing double quotes ('"')
 * from the given string.
 * It returns a new allocated string with these quotes removed.
 * If the input string is empty
 * or null, it returns NULL.
 * 
 * @param str The input string to be trimmed.
 * @return char* A new string with double quotes removed,
 * or NULL if the input was invalid.
 */
static char	*_trim_double_quotes(const char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

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

/**
 * @brief Initializes a new environment node with the given key and value.
 * 
 * This function allocates memory for a new t_environment_node struct.
 * It then copies
 * the provided key and value into the node's fields. If any allocation fails,
 * it prints an error
 * message and returns NULL.
 * 
 * @param key The key to be stored in the node.
 * @param value The value associated with the key.
 * @return t_environment_node* A pointer to the newly created node,
 * or NULL if creation failed.
 */
static t_environment_node	*_node_initialize(char *key, char *value,
			t_bool is_private)
{
	t_environment_node	*ret;

	ret = malloc(sizeof(t_environment_node));
	if (!ret)
		return (NULL);
	ret->key = ft_strdup(key);
	if (ft_strcmp(key, "SHLVL") == 0)
		ret->value = ft_itoa(ft_atoi(value) + 1);
	else
	{
		if (!value)
			ret->value = ft_strdup("");
		else
			ret->value = ft_strdup(value);
	}
	ret->next = NULL;
	ret->is_private = is_private;
	return (ret);
}

/**
 * @brief Creates a new environment node from an entry string.
 * 
 * This function takes an entry string, trims any surrounding double quotes,
 * and splits it into
 * key-value pairs using the '=' delimiter. It validates that exactly two
 * parts exist after splitting.
 * If invalid, it cleans up resources and returns NULL. Otherwise, it 
 * initializes a new node with
 * the parsed values.
 * 
 * @param entry The entry string to parse.
 * @return t_environment_node* A pointer to the newly created node, 
 * or NULL if parsing failed.
 */
t_environment_node	*environment_node_from_entry(const char *entry,
		t_bool is_private)
{
	t_environment_node	*ret;
	char				**params;
	char				*trimmed_entry;
	int					i;

	trimmed_entry = _trim_double_quotes(entry);
	params = ft_split(trimmed_entry, '=');
	free(trimmed_entry);
	if (!params)
		return (NULL);
	ret = _node_initialize(params[0], params[1], is_private);
	i = -1;
	while (params[++i])
		free(params[i]);
	free(params);
	params = NULL;
	return (ret);
}
