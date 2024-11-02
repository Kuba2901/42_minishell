#include <minishell.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper to create a token
Token *create_token(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    return token;
}

// Tokenize function
void tokenize(char *input) {
    char *current = input;
    while (*current != '\0') {
        // Skip whitespace
        if (isspace(*current)) {
            current++;
            continue;
        }

        // Check for && and ||
        if (*current == '&' && *(current + 1) == '&') {
            printf("Token: AND\n");
            current += 2;
        } else if (*current == '|' && *(current + 1) == '|') {
            printf("Token: OR\n");
            current += 2;
        }
        
        // Check for parentheses
        else if (*current == '(') {
            printf("Token: LPAREN\n");
            current++;
        } else if (*current == ')') {
            printf("Token: RPAREN\n");
            current++;
        }

        // Check for single character operators like |
        else if (*current == '|') {
            printf("Token: PIPE\n");
            current++;
        } else if (*current == '<') {
            if (*(current + 1) == '<') {
                printf("Token: HEREDOC\n");
                current += 2;
            } else {
                printf("Token: REDIRECT_IN\n");
                current++;
            }
        } else if (*current == '>') {
            if (*(current + 1) == '>') {
                printf("Token: APPEND\n");
                current += 2;
            } else {
                printf("Token: REDIRECT_OUT\n");
                current++;
            }
        }

        // Handle general words (commands, arguments)
        else {
            char *start = current;
            while (*current != '\0' && !isspace(*current) && !strchr("&|()<>", *current)) {
                current++;
            }
            printf("Token: WORD (%.*s)\n", (int)(current - start), start);
        }
    }
}


int	main(void)
{
	char	*line;
	// char	**sentences;

	while (true)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (!ft_is_whitespace(line))
		{
			tokenize(line);
			// sentences = ft_split_sentences(line);
			// ft_print_enhanced_split(sentences);
			// ft_free_enhanced_split(sentences);
		}
		free(line);
	}
	return (0);
}