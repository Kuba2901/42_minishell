#include <tokenisation.h>

void	handle_arrows(const char **current, t_token_list *list)
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

void	handle_simple_tokens(const char **current, t_token_list *list)
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

void	handle_double_quote(const char **current, t_token_list *list)
{
	const char	*start;

	(*current)++;
	start = *current;
	while (**current != '\0' && **current != '"')
		(*current)++;
	if (**current == '\0')
		return ;
	add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, *current - start)));
	(*current)++;
}

void	handle_word(const char **current, t_token_list *list)
{
	const char	*start;

	start = *current;
	while (**current != '\0' && !ft_is_whitespace(**current) && !ft_strchr("&|()<>", **current))
		(*current)++;
	add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, *current - start)));
}

void	handle_logical(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '&' && *(cur + 1) == '&')
	{
		add_token(list, create_token(TOKEN_AND, NULL));
		(*current) += 2;
	}
	else if (*cur == '|' && *(cur + 1) == '|')
	{
		add_token(list, create_token(TOKEN_OR, NULL));
		(*current) += 2;
	}
}
