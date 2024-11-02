/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:07:28 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 17:59:05 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <libft.h>
# include <readline/readline.h>

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

void	ft_free_enhanced_split(char **s);
void	ft_print_enhanced_split(char **s);
t_bool	ft_is_whitespace(const char *s);
size_t	ft_count_sentences(char *s);
char	**ft_split_sentences(const char *s);
void	tokenize(char *input);

#endif