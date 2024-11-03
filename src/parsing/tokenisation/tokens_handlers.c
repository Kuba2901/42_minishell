/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:37:40 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 17:03:09 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

static void	handle_arrows_left(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*(cur + 1) == '<')
	{
		add_token(list, create_token(TOKEN_HEREDOC, NULL));
		(*current) += 2;
	}
	else
	{
		add_token(list, create_token(TOKEN_REDIRECT_IN, NULL));
		(*current)++;
	}
}

static void	handle_arrows_right(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*(cur + 1) == '>')
	{
		add_token(list, create_token(TOKEN_APPEND, NULL));
		(*current) += 2;
	}
	else
	{
		add_token(list, create_token(TOKEN_REDIRECT_OUT, NULL));
		(*current)++;
	}
}

void	handle_arrows(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '<')
		handle_arrows_left(current, list);
	else if (*cur == '>')
		handle_arrows_right(current, list);
}

void	handle_simple_tokens(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '(')
	{
		add_token(list, create_token(TOKEN_LPAREN, NULL));
		(*current)++;
	}
	else if (*cur == ')')
	{
		add_token(list, create_token(TOKEN_RPAREN, NULL));
		(*current)++;
	}
	else if (*cur == '|')
	{
		add_token(list, create_token(TOKEN_PIPE, NULL));
		(*current)++;
	}
	else if (*cur == '<' || *cur == '>')
		handle_arrows(current, list);
}

void	handle_quoted(const char **current, t_token_list *list, char type)
{
	const char	*start;

	start = *current;
	(*current)++;
	while (**current != '\0' && **current != type)
		(*current)++;
	if (**current == '\0')
	{
		fprintf(stderr, "Error: missing closing quote\n");
		return ;
	}
	(*current)++;
	add_token(list, create_token(TOKEN_WORD,
			ft_substr(start, 0, *current - start)));
}
