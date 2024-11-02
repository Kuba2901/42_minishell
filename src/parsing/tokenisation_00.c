#include <parsing.h>

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    token->type = type;
    if (value)
        token->value = ft_strdup(value);
    else 
        token = NULL;
    return (token);
}

void free_token(t_token *token)
{
    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
}

t_token_list *create_token_list(void)
{
    t_token_list *list;

    list = malloc(sizeof(t_token_list));
    list->head = NULL;
    list->tail = NULL;
    return (list);
}

void free_token_list(t_token_list *list)
{
    t_token_node *current;
    t_token_node *next;

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

void add_token(t_token_list *list, t_token *token)
{
    t_token_node *node;

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
    t_token_node *current;

    current = list->head;
    while (current != NULL)
    {
        printf("Token: ");
        if (current->token->value)
            printf(" (%s)\n", current->token->value);
        else
            printf("\n");
        current = current->next;
    }
}

void tokenize(char *input)
{
    char    *current;
    t_token_list *list;
    
    current = input;
    list = create_token_list();
    while (*current != '\0') {
        if (isspace(*current)) {
            current++;
            continue;
        }

        // Check for && and ||
        if (*current == '&' && *(current + 1) == '&') {
            printf("Token: AND\n");
            add_token(list, create_token(TOKEN_AND, NULL));
            current += 2;
        } else if (*current == '|' && *(current + 1) == '|') {
            printf("Token: OR\n");
            add_token(list, create_token(TOKEN_OR, NULL));
            current += 2;
        }
        
        // Check for parentheses
        else if (*current == '(') {
            printf("Token: LPAREN\n");
            add_token(list, create_token(TOKEN_LPAREN, NULL));
            current++;
        } else if (*current == ')') {
            printf("Token: RPAREN\n");
            add_token(list, create_token(TOKEN_RPAREN, NULL));
            current++;
        }

        // Check for single character operators like |
        else if (*current == '|') {
            printf("Token: PIPE\n");
            add_token(list, create_token(TOKEN_PIPE, NULL));
            current++;
        } else if (*current == '<') {
            if (*(current + 1) == '<') {
                printf("Token: HEREDOC\n");
                add_token(list, create_token(TOKEN_HEREDOC, NULL));
                current += 2;
            } else {
                printf("Token: REDIRECT_IN\n");
                add_token(list, create_token(TOKEN_REDIRECT_IN, NULL));
                current++;
            }
        } else if (*current == '>') {
            if (*(current + 1) == '>') {
                printf("Token: APPEND\n");
                add_token(list, create_token(TOKEN_APPEND, NULL));
                current += 2;
            } else {
                printf("Token: REDIRECT_OUT\n");
                add_token(list, create_token(TOKEN_REDIRECT_OUT, NULL));
                current++;
            }
        }
		// Handle double quotes
		else if (*current == '"') {
			current++;
			char *start = current;
			while (*current != '\0' && *current != '"') {
				current++;
			}
			if (*current == '\0') {
				printf("Error: Unterminated double quote\n");
				break;
			}
			printf("Token: WORD (%.*s)\n", (int)(current - start), start);
            add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, current - start)));
			current++;
		}

        // Handle general words (commands, arguments)
        else {
            char *start = current;
            while (*current != '\0' && !isspace(*current) && !strchr("&|()<>", *current)) {
                current++;
            }
            printf("Token: WORD (%.*s)\n", (int)(current - start), start);
            add_token(list, create_token(TOKEN_WORD, ft_substr(start, 0, current - start)));
        }
    }
    printf("Printing token list:\n");
    print_token_list(list);
    free_token_list(list);
}
