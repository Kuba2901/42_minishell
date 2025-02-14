/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:58:30 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/14 23:00:13 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
