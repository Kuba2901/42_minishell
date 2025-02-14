/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:58:30 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/14 23:26:58 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	_update_keys(t_shell *shell, char *curr_path)
{
	t_environment_node	*tmp;
	t_environment_node	**env;

	env = &shell->env;
	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(environment_list_read("PWD", shell));
		}
		else if (!ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(curr_path);
		}
		tmp = tmp->next;
	}
	return ;
}

char	*_handle_dash(t_shell *shell, char *target)
{
	target = environment_list_read(shell->env, "OLDPWD");
	if (target == NULL)
	{
		printf("%s\n", "cd: OLDPWD not set");
		return ;
	}
	return (target);
}

char	*_handle_home(t_shell *shell, char *target)
{
	target = environment_list_read(shell->env, "HOME");
	if (target == NULL)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	return (target);
}

void	cd(t_shell *shell, char **args)
{
	char	*target;
	char	cwd[1024];

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
	printf("%s\n", target);
	return ;
}
