/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:58:30 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/16 21:19:05 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Updates the PWD and OLDPWD environment variables after a directory change.
 *
 * This function modifies the shell's environment list to reflect the change
 * in the working directory. It updates `OLDPWD` with the previous `PWD` value
 * and sets `PWD` to the new current working directory.
 *
 * @param shell The shell structure containing environment variables.
 * @param curr_path The new current working directory path.
 */
void	_update_keys(t_shell *shell, char *curr_path)
{
	t_environment_node	*node;
	char				*temp;

	if (!shell || !curr_path || !shell->env)
		return ;
	node = environment_list_read_node("OLDPWD", shell);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = ft_strdup(environment_list_read("PWD", shell));
	}
	else
	{
		temp = ft_strjoin("OLDPWD=", environment_list_read("PWD", shell));
		enviroment_node_create(temp, shell, false);
		free(temp);
	}
	node = environment_list_read_node("PWD", shell);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = ft_strdup(curr_path);
	}
}

/**
 * @brief Handles the `cd -` case, switching to the previous directory.
 *
 * This function retrieves the value of `OLDPWD` and returns it.
 * If `OLDPWD` is not set, an error message is printed.
 *
 * @param shell The shell structure containing environment variables.
 * @param target Unused in this function, only for consistency.
 * @return The path stored in `OLDPWD`, or NULL if not set.
 */
char	*_handle_dash(t_shell *shell, char *target)
{
	target = environment_list_read("OLDPWD", shell);
	if (target == NULL)
	{
		printf("%s\n", "cd: OLDPWD not set");
		return (NULL);
	}
	return (target);
}

/**
 * @brief Handles the `cd` command without arguments or with `~`, switching to the home directory.
 *
 * This function retrieves the value of `HOME` and returns it.
 * If `HOME` is not set, an error message is printed.
 *
 * @param shell The shell structure containing environment variables.
 * @param target Unused in this function, only for consistency.
 * @return The path stored in `HOME`, or NULL if not set.
 */
char	*_handle_home(t_shell *shell, char *target)
{
	target = environment_list_read("HOME", shell);
	if (target == NULL)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	return (target);
}

/**
 * @brief Changes the current working directory of the shell.
 *
 * This function implements the `cd` built-in command, allowing users to
 * navigate the filesystem. It supports:
 * - `cd` or `cd ~` to move to the home directory.
 * - `cd -` to move to the previous working directory.
 * - `cd <directory>` to move to the specified directory.
 *
 * If the directory change is successful, it updates the `PWD` and `OLDPWD`
 * environment variables. If it fails, an error message is printed.
 *
 * @param shell A pointer to the shell structure.
 * @param args An array of arguments passed to the `cd` command.
 */
void	builtin_cd(t_shell *shell, char **args)
{
	char	*target;
	char	cwd[1024];

	target = NULL;
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		target = _handle_home(shell, target);
	else if (ft_strcmp(args[1], "-") == 0)
		target = _handle_dash(shell, target);
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		printf("cd: no such file or directory: %s\n", target);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		_update_keys(shell, cwd);
	else
		return (perror("getcwd()"));
	return ;
}
