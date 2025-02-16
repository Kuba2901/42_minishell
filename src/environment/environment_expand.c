/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:16 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 21:27:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

/**
 * @brief Trims the quotes from the given string.
 *
 * This function removes the first character from the input string,
 * effectively trimming the leading quote. It then copies the rest of the
 * string into a newly allocated memory space, excluding the last character
 * (presumably the closing quote).
 *
 * @param str The input string to be trimmed. It is assumed that the string
 *            has quotes at the beginning and end.
 * @return A new string with the quotes removed. The caller is responsible
 *         for freeing the allocated memory.
 */
static char	*_trim_quotes(char *str)
{
	char	*ret;

	ret = malloc((ft_strlen(str) - 1) * sizeof(char));
	str++;
	ft_strlcpy(ret, str, ft_strlen(str));
	return (ret);
}

/**
 * @brief Expands a part of the given string by replacing environment variables with their values.
 *
 * This function takes a string that may contain environment variable references and expands them
 * using the values from the provided shell environment. It identifies the key for the environment
 * variable, retrieves its value, and replaces the key in the string with the corresponding value.
 *
 * @param shell A pointer to the shell structure containing the environment variables.
 * @param str The string containing the environment variable reference to be expanded.
 * @return A new string with the environment variable expanded. The original string is freed.
 */
static char	*_expand_part(t_shell *shell, char *str)
{
	int		key_len;
	char	*rest;
	char	*key;

	key_len = 0;
	while (str[++key_len] && (ft_isalnum(str[key_len]) \
			|| str[key_len] == '_'))
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

/**
 * @brief Concatenates parts of a split string, expanding environment variables if necessary.
 *
 * This function takes a split string and concatenates its parts into a single string.
 * If the string starts with a dollar sign, it expands the environment variables in each part.
 *
 * @param shell Pointer to the shell structure containing environment variables.
 * @param split Array of strings to be concatenated and expanded.
 * @param starts_with_dollar Boolean indicating if the original string starts with a dollar sign.
 * @return A newly allocated string containing the concatenated and expanded parts.
 */
static char	*_put_together(t_shell *shell, char **split,
			t_bool starts_with_dollar)
{
	char	*ret;
	int		i;

	i = -1;
	ret = NULL;
	while (split[++i])
	{
		if (!starts_with_dollar && i == 0)
		{
			ret = ft_join_reassign(ret, split[i]);
			continue ;
		}
		split[i] = ft_join_reassign(ft_strdup("$"), split[i]);
		split[i] = _expand_part(shell, split[i]);
		ret = ft_join_reassign(ret, split[i]);
	}
	free(split);
	return (ret);
}

/**
 * @brief Expands multiple environment variables within a given string.
 *
 * This function takes a string that may contain multiple environment variables
 * and expands them using the provided shell context. It trims any quotes from
 * the input string, splits the string by the dollar sign ('$'), and then
 * reconstructs the string with the expanded variables.
 *
 * @param shell A pointer to the shell context used for variable expansion.
 * @param str The input string containing environment variables to be expanded.
 * @return A newly allocated string with the expanded variables, or NULL if the
 *         input string is NULL.
 */
static char	*_expand_multiple_variables(t_shell *shell, char *str)
{
	char	*trimmed;
	char	**split;
	t_bool	starts_with_dollar;

	if (!str)
		return (NULL);
	trimmed = _trim_quotes(str);
	if (trimmed[0] == '$')
		starts_with_dollar = true;
	else
		starts_with_dollar = false;
	split = ft_split(trimmed, '$');
	free(trimmed);
	return (_put_together(shell, split, starts_with_dollar));
}

/**
 * @brief Expands the value of an environment variable based on the given key.
 *
 * This function takes a key and returns the corresponding environment variable's value.
 * It handles different cases based on the first character of the key:
 * - If the key starts with '$', it skips the '$' and looks up the environment variable.
 * - If the key starts with '"', it expands multiple variables within the key.
 * - If the key starts with '\'', it trims the quotes from the key.
 * - Otherwise, it returns a duplicate of the key.
 *
 * Additionally, if the key is "?", it returns the shell's exit code as a string.
 *
 * @param shell A pointer to the shell structure containing environment variables and exit code.
 * @param key The key of the environment variable to expand.
 * @return A dynamically allocated string containing the expanded value, or NULL if the key is invalid or the value is not found.
 */
char	*env_value_expand(t_shell *shell, char *key)
{
	char	*value;

	if (!key)
		return (NULL);
	if (key[0] == '$')
		key++;
	else if (key[0] == '"')
		return (_expand_multiple_variables(shell, key));
	else if (key[0] == '\'')
		return (_trim_quotes(key));
	else
		return (ft_strdup(key));
	if (ft_strncmp(key, "?", 1) == 0)
		return (ft_itoa(shell->exit_code));
	value = environment_list_read(key, shell);
	if (!value || !*value)
		return (NULL);
	return (ft_strdup(value));
}
