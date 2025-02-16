/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:50:10 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:39:29 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment.h>
#include <minishell.h>

static t_bool	_is_key_valid(char *key)
{
	size_t	i;

	i = 0;
	if (!key || !ft_isalpha(key[0]) || ft_strchr(key, '='))
		return (false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	cleanup_export_args(char **args, char *entry)
{
	int	j;

	j = -1;
	while (args[++j])
		free(args[j]);
	free(args);
	free(entry);
}

static t_bool	process_single_arg(t_shell *shell, char *arg)
{
	t_environment_node	*node;

	if (!_is_key_valid(arg))
	{
		ft_puterror("minishell: export: `", arg, "': not a valid identifier");
		return (true);
	}
	node = environment_list_read_node(arg, shell);
	if (node)
		node->is_private = false;
	else
		enviroment_node_create(arg, shell, false);
	return (false);
}

static t_bool	process_key_value_pair(t_shell *shell, char *arg1, char *arg2)
{
	char	*entry;
	char	**args;
	t_bool	has_error;

	has_error = false;
	entry = ft_strjoin(arg1, arg2);
	if (!entry)
		return (true);
	args = ft_split(entry, '=');
	if (!args)
	{
		free(entry);
		return (true);
	}
	if (_is_key_valid(args[0]))
		enviroment_node_create(entry, shell, false);
	else
	{
		ft_puterror("minishell: export: `", args[0],
			"': not a valid identifier");
		has_error = true;
	}
	cleanup_export_args(args, entry);
	return (has_error);
}

t_bool	builtin_export_export_key_value(t_shell *shell, t_ast_node *node)
{
	size_t	i;
	t_bool	has_error;

	i = 1;
	has_error = false;
	while (node->token_node->args[i])
	{
		if (!node->token_node->args[i + 1])
		{
			has_error = process_single_arg(shell, node->token_node->args[i]);
			break ;
		}
		has_error = process_key_value_pair(shell, node->token_node->args[i],
				node->token_node->args[i + 1]);
		i += 2;
	}
	return (has_error);
}
