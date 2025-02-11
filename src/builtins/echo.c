/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:04:34 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/09 13:26:46 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// when echo's called without arguments it should print two
// newlines, but since we're returning a string, in the case
// it is redirected to a file, it should print only one newline
char	*echo(char **args)
{
	int		newline;
	int		i;
	char	*res;

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
		ft_strjoin(res, '\n');
	return (res);
}
