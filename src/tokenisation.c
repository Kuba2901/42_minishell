#include <minishell.h>

static size_t	ft_countword(char const *s, char const *charset)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && ft_strchr(charset, *s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_strchr(charset, *s))
			s++;
	}
	return (count);
}

static t_bool	ft_is_whitespace(const char *s)
{
	return (*s == ' ' || *s == '\t');
}

size_t	ft_count_tokens(const char *s)
{
	size_t	count;
	t_bool	single_quoted;
	t_bool	double_quoted;

	count = 0;
	single_quoted = false;
	double_quoted = false;
	while (*s)
	{
		while (ft_is_whitespace(s))
			s++;
		if (*s == '"')
		{
			if (double_quoted)
				count++;
			double_quoted = !double_quoted;
			s++;
		}
		else if (*s == '\'')
		{
			if (single_quoted)
				count++;
			single_quoted = !single_quoted;
			s++;
		}
		int	counter = 0; // TEMP
		while (ft_strchr(SPECIAL_CHARSET, *s))
		{
			counter++;
			s++;
		}
		if (counter > 2)
		{
			ft_printf("Wrong input!\n");
			return (0);
		}
		while (!ft_is_whitespace(s) && !ft_strchr(SPECIAL_CHARSET, *s))
			s++;
		count++;
	}
	return (count);
}

char	**ft_enhanced_split(const char *s, const char *charset)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s, charset) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && ft_strchr(charset, *s))
			s++;
		if (*s)
		{
			word_len = 0;
			while (s[word_len] && !ft_strchr(charset, s[word_len]))
				word_len++;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
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