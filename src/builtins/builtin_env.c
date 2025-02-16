/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:48:57 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/16 21:19:38 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

/**
 * @brief Prints the current environment variables.
 *
 * This function prints all the environment variables stored in the shell's
 * environment list. It also sets the shell's exit code to 0 upon completion.
 *
 * @param shell A pointer to the shell structure containing the environment list.
 */
void	builtin_env(t_shell *shell)
{
	environment_list_print(shell, false);
	shell->exit_code = 0;
}
