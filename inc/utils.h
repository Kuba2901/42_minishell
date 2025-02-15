/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:55:15 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:36:27 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef enum s_bool	t_bool;

int		ft_strcmp(const char *s1, const char *s2);
t_bool	ft_is_whitespace(char c);
void	ft_puterror(const char *s, char *arg1, const char *arg2);

#endif