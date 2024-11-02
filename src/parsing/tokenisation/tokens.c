#include <tokenisation.h>


t_token_list	*ft_tokenize(const char *input)
{
	const char		*current;
	t_token_list	*list;
	
	current = input;
	list = init_token_list();
	while (*current != '\0')
	{
		while (*current && ft_is_whitespace(*current))
			current++;
		if ((*current == '&' && *(current + 1) == '&') \
			|| (*current == '|' && *(current + 1) == '|'))
			handle_logical(&current, list);
		else if (ft_strchr("()|<>", *current))
			handle_simple_tokens(&current, list);
		else if (*current == '"')
			handle_double_quote(&current, list);
		else
			handle_word(&current, list);
	}
	return (list);
}
