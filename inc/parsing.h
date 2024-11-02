/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:07:28 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 18:35:33 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <libft.h>
# include <readline/readline.h>
# include <tokenisation.h>

void	ft_free_enhanced_split(char **s);
void	ft_print_enhanced_split(char **s);
t_bool	ft_is_whitespace(const char *s);
size_t	ft_count_sentences(char *s);
char	**ft_split_sentences(const char *s);


#endif