/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:40:53 by jnenczak          #+#    #+#             */
/*   Updated: 2024/02/03 15:40:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	end;

	end = 0;
	while (s[end])
		end++;
	while (end >= 0)
	{
		if (s[end] == (char)c)
			return ((char *)&s[end]);
		end--;
	}
	return (NULL);
}
