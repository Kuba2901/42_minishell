/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:38 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:25:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Retrieves the current working directory.
 *
 * This function uses the getcwd() function to obtain the current working
 * directory and returns it as a dynamically allocated string. The caller
 * is responsible for freeing the allocated memory.
 *
 * @return A pointer to the current working directory string, or NULL if
 *         an error occurs.
 */
char	*builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	return (cwd);
}

/**
 * @brief Executes the built-in pwd command.
 *
 * This function retrieves the current working directory using the 
 * builtin_pwd() function. If the directory is successfully retrieved, 
 * it prints the directory path to the standard output and sets the 
 * shell's exit code to 0. If the directory retrieval fails, it prints 
 * an error message using perror and sets the shell's exit code to 1.
 *
 * @param shell A pointer to the shell structure containing the exit code.
 */
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
