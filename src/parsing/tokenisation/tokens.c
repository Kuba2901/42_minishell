/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:32:21 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/02 19:48:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenisation.h>

void	handle_word(const char **current, t_token_list *list)
{
	const char	*start;

	start = *current;
	while (**current != '\0' && !ft_is_whitespace(**current) \
		&& !ft_strchr("&|()<>", **current))
		(*current)++;
	add_token(list, create_token(TOKEN_WORD,
			ft_substr(start, 0, *current - start)));
}

void	handle_logical(const char **current, t_token_list *list)
{
	const char	*cur;

	cur = *current;
	if (*cur == '&' && *(cur + 1) == '&')
	{
		add_token(list, create_token(TOKEN_AND, NULL));
		(*current) += 2;
	}
	else if (*cur == '|' && *(cur + 1) == '|')
	{
		add_token(list, create_token(TOKEN_OR, NULL));
		(*current) += 2;
	}
}

t_token_list	*ft_tokenize(const char *input)
{
	const char		*current;
	t_token_list	*list;

	current = input;
	list = init_token_list();
	while (*current != '\0')
	{
		while (*current && ft_is_whitespace(*current))
			current++;
		if ((*current == '&' && *(current + 1) == '&') \
			|| (*current == '|' && *(current + 1) == '|'))
			handle_logical(&current, list);
		else if (ft_strchr("()|<>", *current))
			handle_simple_tokens(&current, list);
		else if (*current == '"')
			handle_double_quote(&current, list);
		else
			handle_word(&current, list);
	}
	return (list);
}
