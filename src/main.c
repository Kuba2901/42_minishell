/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:10 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 20:49:14 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, const char **av, const char **envp)
{
	t_shell	shell;
	int		exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	init_shell(&shell, envp);
	signals_setup();
	handle_input(&shell);
	exit_code = shell.exit_code;
	free_resources(&shell);
	return (exit_code);
}
