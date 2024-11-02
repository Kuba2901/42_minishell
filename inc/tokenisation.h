#ifndef TOKENISATION_H
# define TOKENISATION_H
# include <libft.h>
# include <stdlib.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef enum s_token_type {
    TOKEN_WORD,      // General word or command
    TOKEN_AND,       // &&
    TOKEN_OR,        // ||
    TOKEN_LPAREN,    // (
    TOKEN_RPAREN,    // )
    TOKEN_PIPE,      // |
    TOKEN_REDIRECT_IN,   // <
    TOKEN_REDIRECT_OUT,  // >
    TOKEN_APPEND,        // >>
    TOKEN_HEREDOC,       // <<
    // ... Add other tokens as needed
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
}   t_token;

typedef struct s_token_node
{
	t_token             *token;
	struct s_token_node *next;
}   t_token_node;

typedef struct s_token_list
{
	t_token_node *head;
	t_token_node *tail;
}   t_token_list;

t_token         *create_token(t_token_type type, char *value);
t_token_list	*ft_tokenize(const char *input);
void            free_token_list(t_token_list *list);
void            print_token_list(t_token_list *list);

#endif