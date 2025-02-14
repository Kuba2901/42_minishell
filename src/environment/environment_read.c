/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:43 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 22:26:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Reads the value associated with a given key from the 
 * environment list.
 *
 * This function traverses the linked list of environment variables
 * stored in the
 * shell structure and returns the value associated with the
 * specified key.
 *
 * @param key The key to search for in the environment list.
 * @param shell A pointer to the shell structure containing
 * the environment list.
 * @return The value associated with the specified key,
 * or an empty string if the key is not found.
 */
char	*environment_list_read(const char *key, t_shell *shell)
{
	t_environment_node	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

t_environment_node	*environment_list_read_node(const char *key, t_shell *shell)
{
	t_environment_node	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	environment_list_print(t_shell *shell, t_bool is_export)
{
	t_environment_node	*tmp;
	char				*value;

	if (!shell->env)
		return ;
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			value = tmp->value;
		else
			value = "";
		if (is_export)
		{
			if (!tmp->is_private)
				printf("declare -x %s=%s\n", tmp->key, value);
		}
		else
			printf("%s=%s\n", tmp->key, value);
		tmp = tmp->next;
	}
}

void	environment_list_print_sorted(t_shell *shell)
{
	t_shell				tmp;

	tmp.env = environment_list_get_sorted_copy(shell->env);
	environment_list_print(&tmp, true);
	environment_list_clear(&tmp);
}
