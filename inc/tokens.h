/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:11 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:19:23 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <mini_base.h>
# include <utils.h>

typedef enum s_token_type
{
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

/**
 * @struct s_token
 * @brief Represents a token with a type and associated arguments.
 * 
 * @arg s_token::type
 * The type of the token, represented by t_token_type.
 * 
 * @arg s_token::args
 * A pointer to an array of strings (char**) representing
 * the arguments associated with the token, null terminated.
 */
typedef struct s_token_node
{
	t_token_type		type;
	char				**args;
	struct s_token_node	*next;
}	t_token_node;

void			token_delete_all(t_token_node **list);
void			token_delete(t_token_node *token);
t_token_node	*token_create(t_token_type type, char *value);
void			token_print(t_token_node *token);
t_token_node	**tokenise(char *input);
void			handle_simple_tokens(char **current, t_token_node **list);
void			handle_arrows(t_token_node **list, char **current);
void			handle_quoted(char **current, t_token_node **list, char type);
void			handle_word(t_token_node **list, char **current);
void			token_list_print(t_token_node **head);
void			token_append(t_token_node **list, t_token_node *new_node);
size_t			token_count_args(t_token_node *src);

#endif