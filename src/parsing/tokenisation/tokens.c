#include <tokenisation.h>

t_token_list	*ft_tokenize(const char *input)
{
	const char		*current;
	t_token_list	*list;
	const char		*start;
	
	current = input;
	list = init_token_list();
	while (*current != '\0') {
		if (ft_is_whitespace(*current)) {
			current++;
			continue;
		}
		if (*current == '&' && *(current + 1) == '&')
		{
			add_token(list, create_token(TOKEN_AND, NULL));
			current += 2;
		}
		else if (*current == '|' && *(current + 1) == '|')
		{
			add_token(list, create_token(TOKEN_OR, NULL));
			current += 2;
		}
		else if (*current == '(')
		{
			add_token(list, create_token(TOKEN_LPAREN, NULL));
			current++;
		}
		else if (*current == ')')
		{
			add_token(list, create_token(TOKEN_RPAREN, NULL));
			current++;
		}
		else if (*current == '|')
		{
			add_token(list, create_token(TOKEN_PIPE, NULL));
			current++;
		}
		else if (*current == '<')
		{
			if (*(current + 1) == '<')
			{
				add_token(list, create_token(TOKEN_HEREDOC, NULL));
				current += 2;
			}
			else
			{
				add_token(list, create_token(TOKEN_REDIRECT_IN, NULL));
				current++;
			}
		}
		else if (*current == '>')
		{
			if (*(current + 1) == '>')
			{
				add_token(list, create_token(TOKEN_APPEND, NULL));
				current += 2;
			}
			else
			{
				add_token(list, create_token(TOKEN_REDIRECT_OUT, NULL));
				current++;
			}
		}
		else if (*current == '"')
		{
			current++;
			start = current;
			while (*current != '\0' && *current != '"')
			{
				current++;
			}
			if (*current == '\0')
			{
				printf("Error: Unterminated double quote\n");
				break;
			}
			add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, current - start)));
			current++;
		}
		else
		{
			start = current;
			while (*current != '\0' && !ft_is_whitespace(*current) && !ft_strchr("&|()<>", *current))
			{
				current++;
			}
			add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, current - start)));
		}
	}
	return (list);
}
