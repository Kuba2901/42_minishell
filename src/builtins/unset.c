/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:05:37 by gromiti           #+#    #+#             */
/*   Updated: 2025/02/10 10:12:11 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_env_list *env, char **args)
{
	t_env_node	*node;
	int			i;

	if (args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return;
	}
	i = 1;
	while (args[i] != NULL)
	{
		node = env_list_read_node(env, args[i]);
		if (node != NULL)
		{
			env_list_delete_node(env, args[i]);
		}
		i++;
	}
	printf("\n");
}