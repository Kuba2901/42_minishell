#include <tokenisation.h>

t_bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

t_token *create_token(t_token_type type, char *value)
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

static void    free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

static t_token_list    *init_token_list(void)
{
	t_token_list    *list;

	list = malloc(sizeof(t_token_list));
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

void    free_token_list(t_token_list *list)
{
	t_token_node    *current;
	t_token_node    *next;

	if (list == NULL)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_token(current->token);
		free(current);
		current = next;
	}
	free(list);
}

static void    add_token(t_token_list *list, t_token *token)
{
	t_token_node    *node;

	node = malloc(sizeof(t_token_node));
	node->token = token;
	node->next = NULL;
	if (list->tail)
	{
		list->tail->next = node;
		list->tail = node;
	}
	else
	{
		list->head = node;
		list->tail = node;
	}
}

void print_token_list(t_token_list *list)
{
	t_token_node    *current;

	if (list == NULL)
		return ;
	current = list->head;
	while (current != NULL)
	{
		printf("Token: (%d)", current->token->type);
		if (current->token->value != NULL)
			printf(" (%s)\n", current->token->value);
		else
			printf("\n");
		current = current->next;
	}
}

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
