/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:41 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/14 22:26:37 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <mini_base.h>

typedef struct s_shell	t_shell;

typedef struct s_environment_node
{
	char						*key;
	char						*value;
	struct s_environment_node	*next;
	t_bool						is_private;
}	t_environment_node;

void				environment_list_clear(t_shell *shell);
char				*environment_list_read(const char *key, t_shell *shell);
void				enviroment_node_delete(const char *key, t_shell *shell);
t_environment_node	*environment_list_initialize(const char **envp);
t_environment_node	*enviroment_node_create(const char *entry, t_shell *shell,
						t_bool is_private);
char				*env_value_expand(t_shell *shell, char *key);
char				**environment_serialize(t_shell *shell);
void				environment_serialized_list_clear(char **list);
void				environment_list_print(t_shell *shell,
						t_bool is_export);
t_environment_node	*environment_node_from_entry(const char *entry,
						t_bool is_private);
void				environment_list_print_sorted(t_shell *shell);
t_environment_node	*environment_list_get_sorted_copy(
						t_environment_node *original);
t_environment_node	*environment_list_read_node(const char *key, t_shell *shell);

#endif