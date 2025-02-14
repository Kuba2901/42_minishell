/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:58:30 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/14 10:11:24 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd (t_shell *shell, char **args)
{
	char	prev_path[1024];
	char	cwd[1024];
	char	*target;

	if (getcwd(prev_path, sizeof(prev_path)) == NULL)
	{
		perror("getcwd() error");
		return;
	}
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		target = environment_list_read(shell->env, "HOME");
		if (target == NULL)
		{
			printf("cd: HOME not set\n");
			return;
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = environment_list_read(shell->env, "OLDPWD");
		if (target == NULL)
		{
			target = prev_path;
			// export OLDPWD?
		}
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		printf("cd: no such file or directory: %s\n", target);
		return;
	}
	printf("%s\n", target);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// both update OLDPWD and PWD
	}
	else
	{
		perror("getcwd(");
		return;
	}
}