/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:43 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:28:21 by jnenczak         ###   ########.fr       */
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

/**
 * @brief Reads a node from the environment list based on the given key.
 *
 * This function searches through the environment list in the shell structure
 * to find a node that matches the provided key. If a matching node is found,
 * it is returned. Otherwise, the function returns NULL.
 *
 * @param key The key to search for in the environment list.
 * @param shell A pointer to the shell structure containing the environment list.
 * @return t_environment_node* A pointer to the matching environment node, or NULL if not found.
 */
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

/**
 * @brief Prints the environment variables in the shell.
 *
 * This function iterates through the linked list of environment variables
 * and prints each variable in the format specified by the `is_export` flag.
 *
 * @param shell Pointer to the shell structure containing the environment list.
 * @param is_export Boolean flag indicating the format of the output:
 *                  - If true, prints variables in the format used by the `export` command.
 *                  - If false, prints variables in the standard key=value format.
 *
 * @return void
 */
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

/**
 * @brief Prints the environment variables in sorted order.
 *
 * This function creates a temporary copy of the environment variables,
 * sorts them, and then prints them. After printing, it clears the temporary
 * environment list to free up memory.
 *
 * @param shell A pointer to the shell structure containing the environment list.
 */
void	environment_list_print_sorted(t_shell *shell)
{
	t_shell				tmp;

	tmp.env = environment_list_get_sorted_copy(shell->env);
	environment_list_print(&tmp, true);
	environment_list_clear(&tmp);
}
