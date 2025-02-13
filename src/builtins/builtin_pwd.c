/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:38 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:01:40 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

char	*builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	return (cwd);
}

void	execute_builtin_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = builtin_pwd();
	if (pwd == NULL)
	{
		perror("pwd");
		shell->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		shell->exit_code = 0;
	}
	free(pwd);
}
