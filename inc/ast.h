#ifndef AST_H
# define AST_H

# include <tokenisation.h>

typedef enum s_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIRECT_IN,
	AST_REDIRECT_OUT,
	AST_APPEND,
	AST_HEREDOC
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*primary_parse(t_token_list *tokens);
void		print_ast(t_ast_node *node);
void		free_ast(t_ast_node *node);

#endif