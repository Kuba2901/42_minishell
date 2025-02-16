/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:55:15 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/16 20:50:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef enum s_bool		t_bool;
typedef struct s_shell	t_shell;

int		ft_strcmp(const char *s1, const char *s2);
t_bool	ft_is_whitespace(char c);
void	ft_puterror(const char *s, char *arg1, const char *arg2);
void	clear_screen_ensure_cursor_visible(void);
void	free_resources(t_shell *shell);
void	init_shell(t_shell *shell, const char **envp);
void	handle_input(t_shell *shell);

#endif