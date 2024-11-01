#include <minishell.h>

static t_bool	ft_is_whitespace(const char *s)
{
	return (*s == ' ' || *s == '\t');
}

size_t	ft_count_sentences(char *s)
{
	if (*s == '\0')
		return (0);
	while (ft_is_whitespace(s))
		s++;
	if (*s == '\0')
		return (0);

	char	*marker1;
	char	*marker2;

	marker1 = ft_strnstr(s, ";", ft_strlen(s));
	marker2 = ft_strnstr(s, "&&", ft_strlen(s));
	if (marker1 && marker2)
	{
		if (marker1 < marker2)
			return 1 + ft_count_sentences(marker1 + 1);
		else
			return 1 + ft_count_sentences(marker2 + 2);
	}
	else if (marker1)
		return 1 + ft_count_sentences(marker1 + 1);
	else if (marker2)
		return 1 + ft_count_sentences(marker2 + 2);
	return 1;
}

static char	**ft_split_sentences_rec(const char *s, char **ret, size_t index)
{
	char	*marker1;
	char	*marker2;
	size_t	len;

	if (*s == '\0')
		return (ret);
	while (*s && ft_is_whitespace(s))
		s++;
	marker1 = ft_strnstr(s, ";", ft_strlen(s));
	marker2 = ft_strnstr(s, "&&", ft_strlen(s));
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
	ret[index] = ft_substr(s, 0, len);
	if (marker1 && marker2)
	{
		if (marker1 < marker2)
			return ft_split_sentences_rec(marker1 + 1, ret, index + 1);
		else
			return ft_split_sentences_rec(marker2 + 2, ret, index + 1);
	}
	else if (marker1)
		return ft_split_sentences_rec(marker1 + 1, ret, index + 1);
	else if (marker2)
		return ft_split_sentences_rec(marker2 + 2, ret, index + 1);
	else
		return (ret);
}

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