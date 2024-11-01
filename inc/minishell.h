#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# define DOUBLE_SPECIAL_CHARSET "|&<>"
# define SINGLE_SPECIAL_CHARSET "="
typedef enum {
	false,
	true
} t_bool;

void	ft_print_enhanced_split(char **s);
void	ft_free_enhanced_split(char **s);
size_t	ft_count_sentences(char *s);
char	**ft_split_sentences(const char *s);
#endif