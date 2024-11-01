/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:06:57 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/01 20:07:02 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parsing.h>

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * This function iterates through an array of strings, freeing each string
 * and then setting the pointer to NULL. The array itself is not freed.
 *
 * @param s A pointer to the array of strings to be freed. The array must be
 *          NULL-terminated.
 */
void	ft_free_enhanced_split(char **s)
{
	while (*s != NULL)
	{
		free(*s);
		s++;
	}
	s = NULL;
}

void	ft_print_enhanced_split(char **s)
{
	while (*s)
		ft_printf("%s\n", *s++);
}

t_bool	ft_is_whitespace(const char *s)
{
	return (*s == ' ' || *s == '\t');
}
