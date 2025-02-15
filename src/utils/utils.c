/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:56:27 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:38:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <mini_base.h>

/**
 * @brief Compares two null-terminated strings lexicographically.
 *
 * This function compares the two strings s1 and s2. It returns an integer
 * less than, equal to, or greater than zero if s1 is found, respectively,
 * to be less than, to match, or be greater than s2.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function checks if the given character c is a whitespace character.
 * Whitespace characters include space (' '),
 * horizontal tab ('\t'), newline ('\n'),
 * and carriage return ('\r').
 *
 * @param c The character to be checked.
 * @return A boolean value indicating whether
 * the character is a whitespace character.
 */
t_bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void	ft_puterror(const char *s, char *arg1, const char *arg2)
{
	if (!s || !arg1)
		return ;
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, arg1, ft_strlen(arg1));
	if (arg2)
		write(STDERR_FILENO, arg2, ft_strlen(arg2));
	write(STDERR_FILENO, "\n", 1);
}
