/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:16 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 17:25:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

static char	*_trim_double_quotes(char *str)
{
	char	*ret;

	ret = malloc((ft_strlen(str) - 1) * sizeof(char));
	str++;
	ft_strlcpy(ret, str, ft_strlen(str));
	return (ret);
}

static char	*_expand_multiple_variables(t_shell *shell, char *str)
{
	char	*trimmed;
	char	*ret;
	char	**split;
	int		i;

	trimmed = _trim_double_quotes(str);
	split = ft_split(trimmed, ' ');
	ret = ft_strdup("");
	i = -1;
	while (split[++i])
	{
		ret = ft_join_reassign(ret, env_value_expand(shell, split[i]));
		ret = ft_join_reassign(ret, ft_strdup(" "));
	}
	return (ret);
}

char	*env_value_expand(t_shell *shell, char *key)
{
	char	*value;

	if (key[0] == '$')
		key++;
	else if (key[0] == '"')
		return (_expand_multiple_variables(shell, key));
	else
		return (ft_strdup(key));
	if (ft_strncmp(key, "?", 1) == 0)
		return (ft_itoa(shell->exit_code));
	value = environment_list_read(key, shell);
	if (!value || !*value)
		return (NULL);
	return (ft_strdup(value));
}
