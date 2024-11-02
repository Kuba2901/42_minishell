/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:07:21 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 17:39:06 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <parsing.h>
# define DOUBLE_SPECIAL_CHARSET "|&<>"
# define SINGLE_SPECIAL_CHARSET "="
# define PROMPT "minishell > "

// TEST
typedef enum {
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
} TokenType;

typedef struct {
    TokenType type;
    char *value;  // Store actual text of the token, if needed
} Token;


#endif