#ifndef PARSING_H
# define PARSING_H
typedef enum {
	false,
	true
} t_bool;

void	ft_free_enhanced_split(char **s);
void	ft_print_enhanced_split(char **s);
t_bool	ft_is_whitespace(const char *s);
size_t	ft_count_sentences(char *s);
char	**ft_split_sentences(const char *s);

#endif