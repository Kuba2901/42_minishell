/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_serialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:09 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 20:54:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

static int	environment_list_count(t_shell *shell)
{
	t_environment_node	*env;
	int					count;

	if (!shell->env)
		return (0);
	env = shell->env;
	count = 0;
	while (env)
	{
		if (!env->is_private)
			count++;
		env = env->next;
	}
	return (count);
}

char	**environment_serialize(t_shell *shell)
{
	char				**ret;
	int					list_count;
	t_environment_node	*env;

	list_count = environment_list_count(shell);
	if (!list_count)
		return (NULL);
	ret = malloc(sizeof(char *) * (list_count + 1));
	if (!ret)
		return (NULL);
	ret[list_count] = NULL;
	env = shell->env;
	list_count = -1;
	while (env)
	{
		if (!env->is_private)
		{
			ret[++list_count] = ft_strjoin(env->key, "=");
			ret[list_count] = ft_join_reassign(ret[list_count], env->value);
		}
		env = env->next;
	}
	return (ret);
}

void	environment_serialized_list_clear(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}
