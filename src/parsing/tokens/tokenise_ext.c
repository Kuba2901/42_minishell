/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:18:55 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/13 14:20:56 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

size_t	token_count_args(t_token_node *src)
{
	size_t			i;
	t_token_node	*temp;

	i = 0;
	temp = src->next;
	while (temp != NULL)
	{
		if (src->type == temp->type \
			&& src->type == TOKEN_STRING)
		{
			i++;
			temp = temp->next;
		}
		else
			break ;
	}
	return (i);
}
