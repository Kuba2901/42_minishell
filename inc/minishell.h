#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# define DOUBLE_SPECIAL_CHARSET "|&<>"
# define SINGLE_SPECIAL_CHARSET "="
typedef enum {
	false,
	true
} t_bool;

char	**ft_enhanced_split(char const *s, char const *charset);
void	ft_print_enhanced_split(char **s);
void	ft_free_enhanced_split(char **s);
size_t	ft_count_tokens(const char *s);
size_t	ft_count_sentences(char *s);

#endif