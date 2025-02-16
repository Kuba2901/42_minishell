/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:09 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:29:08 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Counts the number of non-private environment variables in the shell.
 *
 * This function iterates through the linked list of environment variables
 * in the shell and counts the number of variables that are not marked as private.
 *
 * @param shell A pointer to the shell structure containing the environment list.
 * @return The number of non-private environment variables. Returns 0 if the environment list is NULL.
 */
static int	environment_list_count(t_shell *shell)
{
	t_environment_node	*env;
	int					count;

	if (!shell->env)
		return (0);
	env = shell->env;
	count = 0;
	while (env)
	{
		if (!env->is_private)
			count++;
		env = env->next;
	}
	return (count);
}

/**
 * @brief Serializes the environment variables from the shell into an array of strings.
 *
 * This function takes the environment variables stored in the shell's environment list
 * and serializes them into an array of strings, where each string is in the format "key=value".
 * Private environment variables (marked by `is_private`) are excluded from the serialization.
 *
 * @param shell A pointer to the shell structure containing the environment list.
 * @return A NULL-terminated array of strings representing the serialized environment variables.
 *         Returns NULL if there are no environment variables or if memory allocation fails.
 */
char	**environment_serialize(t_shell *shell)
{
	char				**ret;
	int					list_count;
	t_environment_node	*env;

	list_count = environment_list_count(shell);
	if (!list_count)
		return (NULL);
	ret = malloc(sizeof(char *) * (list_count + 1));
	if (!ret)
		return (NULL);
	ret[list_count] = NULL;
	env = shell->env;
	list_count = -1;
	while (env)
	{
		if (!env->is_private)
		{
			ret[++list_count] = ft_strjoin(env->key, "=");
			ret[list_count] = ft_join_reassign(ret[list_count], env->value);
		}
		env = env->next;
	}
	return (ret);
}

/**
 * @brief Frees a list of strings and the list itself.
 *
 * This function iterates through a list of strings, freeing each string,
 * and then frees the list itself.
 *
 * @param list A null-terminated array of strings to be freed.
 */
void	environment_serialized_list_clear(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}
