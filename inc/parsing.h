/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:07:28 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/01 20:09:00 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum s_bool
{
	false,
	true
}	t_bool;

void	ft_free_enhanced_split(char **s);
void	ft_print_enhanced_split(char **s);
t_bool	ft_is_whitespace(const char *s);
size_t	ft_count_sentences(char *s);
char	**ft_split_sentences(const char *s);

#endif