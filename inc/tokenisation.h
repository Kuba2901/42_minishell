/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:43:03 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 17:02:09 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H
# include <libft.h>
# include <stdlib.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
}	t_token_list;

t_token_list	*init_token_list(void);
void			add_token(t_token_list *list, t_token *token);
t_bool			ft_is_whitespace(char c);
t_token			*create_token(t_token_type type, char *value);
t_token_list	*ft_tokenize(const char *input);
void			free_token_list(t_token_list *list);
void			print_token_list(t_token_list *list);
void			free_token(t_token *token);
void			handle_arrows(const char **current, t_token_list *list);
void			handle_simple_tokens(const char **current, t_token_list *list);
void			handle_quoted(const char **current, t_token_list *list, char type);
void			handle_word(const char **current, t_token_list *list);
void			handle_logical(const char **current, t_token_list *list);
const char		*get_token_description(t_token_type type);

#endif