/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:49:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/03/10 14:03:42 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	converted;

	converted = (char)c;
	while (*s)
	{
		if ((*s) == converted)
			return ((char *)s);
		s++;
	}
	if ((*s) == converted)
		return ((char *)s);
	return (NULL);
}
