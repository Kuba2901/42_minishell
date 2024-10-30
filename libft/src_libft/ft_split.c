/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:43:12 by jnenczak          #+#    #+#             */
/*   Updated: 2024/02/03 15:43:13 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_alloc(char **arr, char const *s, char c)
{
	char		**tmp_arr;
	char const	*tmp_str;

	tmp_str = s;
	tmp_arr = arr;
	while (*tmp_str)
	{
		while (*s == c)
			++s;
		tmp_str = s;
		while (*tmp_str && *tmp_str != c)
			++tmp_str;
		if (*tmp_str == c || tmp_str > s)
		{
			*tmp_arr = ft_substr(s, 0, tmp_str - s);
			s = tmp_str;
			++tmp_arr;
		}
	}
	*tmp_arr = NULL;
}

static int	ft_count_words(char const *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++count;
		while (*s && *s != c)
			++s;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(s) * (ft_count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	ft_alloc(ret, s, c);
	return (ret);
}
