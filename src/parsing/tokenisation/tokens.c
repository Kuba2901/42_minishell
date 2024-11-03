/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:32:21 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/03 17:06:00 by jnenczak         ###   ########.fr       */
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

static void	ft_join_tokens(t_token_list *src)
{
	t_token_node	*node1;
	t_token_node	*node2;
	t_token_node	*temp;

	if (src == NULL || src->head == NULL)
		return ;
	node1 = src->head;
	while (node1 != NULL)
	{
		node2 = node1->next;
		while (node2 != NULL)
		{
			if (node1->token->type == node2->token->type \
				&& node1->token->type == TOKEN_WORD)
			{
				node1->token->value = ft_join_reassign(
						node1->token->value, ft_strdup(" "));
				node1->token->value = ft_join_reassign(
						node1->token->value, node2->token->value);
				temp = node2->next;
				node1->next = temp;
				free(node2);
				node2 = temp;
			}
			else
				break ;
		}
		node1 = node1->next;
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
		else if (*current == '"' || *current == '\'')
			handle_quoted(&current, list, *current);
		else
			handle_word(&current, list);
	}
	ft_join_tokens(list);
	return (list);
}
