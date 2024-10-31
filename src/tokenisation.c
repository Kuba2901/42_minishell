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