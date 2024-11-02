#include <tokenisation.h>

static void	skip_init_whitespace(const char **current)
{
	while (ft_is_whitespace(**current))
		(*current)++;
}

static void	handle_arrows(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '<')
	{
		if (*(cur + 1) == '<')
		{
			add_token(list, create_token(TOKEN_HEREDOC, NULL));
			(*current) += 2;
		}
		else
		{
			add_token(list, create_token(TOKEN_REDIRECT_IN, NULL));
			(*current)++;
		}
	}
	else if (*cur == '>')
	{
		if (*(cur + 1) == '>')
		{
			add_token(list, create_token(TOKEN_APPEND, NULL));
			(*current) += 2;
		}
		else
		{
			add_token(list, create_token(TOKEN_REDIRECT_OUT, NULL));
			(*current)++;
		}
	}
}

static void	handle_simple_tokens(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '(')
	{
		add_token(list, create_token(TOKEN_LPAREN, NULL));
		(*current)++;
	}
	else if (*cur == ')')
	{
		add_token(list, create_token(TOKEN_RPAREN, NULL));
		(*current)++;
	}
	else if (*cur == '|')
	{
		add_token(list, create_token(TOKEN_PIPE, NULL));
		(*current)++;
	}
	else if (*cur == '<' || *cur == '>')
		handle_arrows(current, list);	
}

t_token_list	*ft_tokenize(const char *input)
{
	const char		*current;
	t_token_list	*list;
	const char		*start;
	
	current = input;
	list = init_token_list();
	while (*current != '\0') {
		skip_init_whitespace(&current);
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
		else if (ft_strchr("()|<>", *current))
			handle_simple_tokens(&current, list);
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
				current++;
			add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, current - start)));
		}
	}
	return (list);
}
