/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:03:12 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 17:15:31 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Counts the number of sentences in a given string `s`.
 * A sentence is defined as a sequence of characters separated by either
 * a semicolon (';') or a double ampersand ('&&').
 *
 * @param s The input string to be analyzed.
 * @return The number of sentences found in the input string.
 *
 * The function works by recursively finding the first occurrence of either
 * a semicolon or a double ampersand, and then counting the sentences in the
 * remaining substring. Whitespace at the beginning of the string is ignored.
 */
size_t	ft_count_sentences(char *s)
{
	char	*marker1;
	char	*marker2;

	if (*s == '\0')
		return (0);
	while (ft_is_whitespace(s))
		s++;
	if (*s == '\0')
		return (0);
	marker1 = ft_strnstr(s, "||", ft_strlen(s));
	marker2 = ft_strnstr(s, "&&", ft_strlen(s));
	if (marker1 && marker2)
	{
		if (marker1 < marker2)
			return (1 + ft_count_sentences(marker1 + 1));
		else
			return (1 + ft_count_sentences(marker2 + 2));
	}
	else if (marker1)
		return (1 + ft_count_sentences(marker1 + 1));
	else if (marker2)
		return (1 + ft_count_sentences(marker2 + 2));
	return (1);
}

/**
 * @brief Calculates the length of a substring up to the first occurrence
 * of either marker1 or marker2, excluding any trailing whitespace.
 *
 * This function determines the length of the substring starting from the 
 * beginning of the string `s` and ending at the first occurrence of either 
 * `marker1` or `marker2`. If both markers are present, the function uses 
 * the one that appears first in the string. If neither marker is present, 
 * the length of the entire string `s` is used. The function also trims any 
 * trailing whitespace from the calculated length.
 *
 * @param marker1 A pointer to the first marker in the string `s`.
 * @param marker2 A pointer to the second marker in the string `s`.
 * @param s The input string.
 * @return The length of the substring up to the first marker, excluding 
 * trailing whitespace.
 */
static	size_t	ft_split_sentences_rec_get_len(char *marker1,
	char *marker2, const char *s)
{
	size_t	len;
	size_t	no_trailing_whitespace_len;

	if (marker1 && marker2)
	{
		if (marker1 < marker2)
			len = marker1 - s;
		else
			len = marker2 - s;
	}
	else if (marker1)
		len = marker1 - s;
	else if (marker2)
		len = marker2 - s;
	else
		len = ft_strlen(s);
	no_trailing_whitespace_len = len - 1;
	while (no_trailing_whitespace_len > 0 \
		&& ft_is_whitespace(s + no_trailing_whitespace_len))
		no_trailing_whitespace_len--;
	if (no_trailing_whitespace_len > 0)
		len = no_trailing_whitespace_len + 1;
	return (len);
}

/**
 * @brief Recursively splits a string into sentences based on delimiters 
 * ";" and "&&".
 *
 * This function takes a string and splits it into sentences using the 
 * delimiters ";" and "&&". It recursively processes the string, storing 
 * each sentence in the provided array `ret`.
 *
 * @param s The input string to be split.
 * @param ret The array to store the split sentences.
 * @param index The current index in the array `ret` where the next sentence 
 * should be stored.
 * @return A pointer to the array `ret` containing the split sentences.
 */
static char	**ft_split_sentences_rec(const char *s, char **ret, size_t index)
{
	char	*marker1;
	char	*marker2;
	size_t	len;

	if (*s == '\0')
		return (ret);
	while (*s && ft_is_whitespace(s))
		s++;
	marker1 = ft_strnstr(s, "||", ft_strlen(s));
	marker2 = ft_strnstr(s, "&&", ft_strlen(s));
	len = ft_split_sentences_rec_get_len(marker1, marker2, s);
	ret[index] = ft_substr(s, 0, len);
	if (marker1 && marker2)
	{
		if (marker1 < marker2)
			return (ft_split_sentences_rec(marker1 + 1, ret, index + 1));
		else
			return (ft_split_sentences_rec(marker2 + 2, ret, index + 1));
	}
	else if (marker1)
		return (ft_split_sentences_rec(marker1 + 1, ret, index + 1));
	else if (marker2)
		return (ft_split_sentences_rec(marker2 + 2, ret, index + 1));
	else
		return (ret);
}

/**
 * ft_split_sentences - Splits a string into an array of sentences.
 * @s: The input string to be split.
 *
 * This function takes a string and splits it into an array of sentences.
 * It first counts the number of sentences in the string using the 
 * ft_count_sentences function. Then, it allocates memory for an array 
 * of strings to hold the sentences. If memory allocation fails, it 
 * returns NULL. Finally, it calls the ft_split_sentences_rec function 
 * to perform the actual splitting and returns the resulting array.
 *
 * Return: A pointer to an array of strings (sentences), or NULL if 
 * memory allocation fails.
 */
char	**ft_split_sentences(const char *s)
{
	size_t	count;
	char	**ret;

	count = ft_count_sentences((char *)s);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = NULL;
	return (ft_split_sentences_rec(s, ret, 0));
}
