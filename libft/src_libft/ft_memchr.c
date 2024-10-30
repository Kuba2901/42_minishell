/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:50:54 by jnenczak          #+#    #+#             */
/*   Updated: 2024/02/02 17:13:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*curr;

	curr = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*curr++ == (unsigned char)c)
			return ((void *)--curr);
	}
	return (NULL);
}
