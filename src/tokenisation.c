#include <minishell.h>

static t_bool	ft_is_whitespace(const char *s)
{
	return (*s == ' ' || *s == '\t');
}

/*
static t_bool	ft_check_char_valid_equals(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') \
		|| (c >= 'a' && c <= 'z'));
}
*/

/*
static t_bool	ft_check_equals(const char *s)
{
	size_t	i;
	char	prev;
	char	next;

	if (ft_strchr(s, '=') == NULL)
		return (true);
	i = -1;
	while (s[++i])
	{
		if (i != 0 && s[i] != '\0')
		{
			prev = s[i - 1];
			next = s[i + 1];
			if (!ft_check_char_valid_equals(prev) || !ft_check_char_valid_equals(next))
				return (false);
		}
	}
	return (true);
}
*/

/*

static t_bool	ft_specials_valid(const char *s)
{
	unsigned int	double_counter;
	unsigned int	single_counter;

	double_counter = 0;
	single_counter = 0;

	while (ft_strchr(SINGLE_SPECIAL_CHARSET, *s) && *s)
	{
		single_counter++;
		s++;
	}

	while (ft_strchr(DOUBLE_SPECIAL_CHARSET, *s) && *s)
	{
		double_counter++;
		s++;
	}
	if (single_counter && double_counter)
	{
		printf("Wrong input!\n");
		return (false);
	}
	if (single_counter > 1)
	{
		ft_printf("Wrong input!\n");
		return (false);
	} 
	if (double_counter > 2)
	{
		ft_printf("Wrong input!\n");
		return (false);
	}
	return (true);
}
*/


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

/*
const char	*ft_split_sentences(const char *s)
{

}
*/

size_t	ft_count_tokens(const char *s)
{
	size_t	count;
	// t_bool	single_quoted;
	// t_bool	double_quoted;

	count = 0;
	// single_quoted = false;
	// double_quoted = false;
	while (*s)
	{
		while (ft_is_whitespace(s) && *s)
			s++;
		// if (*s == '"')
		// {
		// 	if (double_quoted)
		// 		count++;
		// 	double_quoted = !double_quoted;
		// 	s++;
		// }
		// else if (*s == '\'')
		// {
		// 	if (single_quoted)
		// 		count++;
		// 	single_quoted = !single_quoted;
		// 	s++;
		// }
		int	counter = 0; // TEMP
		while (ft_strchr(DOUBLE_SPECIAL_CHARSET, *s) && *s)
		{
			counter++;
			s++;
		}
		if (counter > 2)
		{
			ft_printf("Wrong input!\n");
			return (0);
		} else if (counter > 0) {
			count++;
		}
		counter = 0;
		// printf("[1] Str: %s, count: %ld\n", s, count);
		while (!ft_is_whitespace(s) && !ft_strchr(DOUBLE_SPECIAL_CHARSET, *s) && !ft_strchr(SINGLE_SPECIAL_CHARSET, *s) && *s)
		{
			s++;
			counter++;
		}
		if (counter != 0)
			count++;
		// printf("[2] Str: %s, count: %ld\n", s, count);
	}
	return (count);
}

// char	**ft_enhanced_split(const char *s, const char *charset)
// {
// 	char	**lst;
// 	size_t	word_len;
// 	int		i;

// 	lst = (char **)malloc((ft_countword(s, charset) + 1) * sizeof(char *));
// 	if (!s || !lst)
// 		return (0);
// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && ft_strchr(charset, *s))
// 			s++;
// 		if (*s)
// 		{
// 			word_len = 0;
// 			while (s[word_len] && !ft_strchr(charset, s[word_len]))
// 				word_len++;
// 			lst[i++] = ft_substr(s, 0, word_len);
// 			s += word_len;
// 		}
// 	}
// 	lst[i] = NULL;
// 	return (lst);
// }

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