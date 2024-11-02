#include <tokenisation.h>

t_bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else 
		token->value = NULL;
	return (token);
}

void    free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}