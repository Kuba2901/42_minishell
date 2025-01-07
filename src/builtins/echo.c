/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:04:34 by gromiti           #+#    #+#             */
/*   Updated: 2025/01/07 19:56:40 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*echo(char **args)
{
	int	    newline;
	int	    i;
    char    *res;

	if (args[i] == NULL)
		return (0);
	newline = 0;
	i = 0;
	res = (char *)malloc(sizeof(char) * 1);
	res = '\n';
	while (args[i++] != NULL)
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
			newline = 1;
		else
		{
			res = ft_strjoin(res, args[i]);
			if (args[i + 1] != NULL)
				res = ft_strjoin(res, " ");
		}
	}
	if (!newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
