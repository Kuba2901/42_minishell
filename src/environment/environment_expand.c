/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:16 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 19:49:50 by jnenczak         ###   ########.fr       */
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

static char	*_expand_part(t_shell *shell, char *str)
{	int		key_len;
	char	*rest;
	char	*key;

	key_len = -1;
	while (str[++key_len] && (ft_isalnum(str[key_len]) || str[key_len] == '_')) // TOOD: Check these
		;
	rest = ft_strdup(str + key_len);
	key = ft_substr(str, 0, key_len);
	free(str);
	str = env_value_expand(shell, key);
	free(key);
	str = ft_join_reassign(str, rest);
	key = NULL;
	return (str);
}

static char	*_expand_multiple_variables(t_shell *shell, char *str)
{
	char	*trimmed;
	char	**split;
	t_bool	starts_with_dollar;
	int		i;
	char	*ret;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	ret = NULL;
	trimmed = _trim_double_quotes(str);
	if (trimmed[0] == '$')
		starts_with_dollar = true;
	else
		starts_with_dollar = false;
	split = ft_split(trimmed, '$');
	free(trimmed);
	i = -1;
	while (split[++i])
	{
		if (!starts_with_dollar && i == 0)
			continue ;
		split[i] = _expand_part(shell, split[i]);
		ret = ft_join_reassign(ret, split[i]);
	}
	free(split);
	return (ret);
}

char	*env_value_expand(t_shell *shell, char *key)
{
	char	*value;

	if (key[0] == '$')
		key++;
	else if (key[0] == '"')
		return (_expand_multiple_variables(shell, key));
	if (ft_strncmp(key, "?", 1) == 0)
		return (ft_itoa(shell->exit_code));
	value = environment_list_read(key, shell);
	if (!value || !*value)
		return (NULL);
	return (ft_strdup(value));
}
