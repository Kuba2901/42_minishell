/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:04:26 by jnenczak          #+#    #+#             */
/*   Updated: 2024/01/11 15:12:52 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	i;

	dest_len = 0;
	while (dest_len < dstsize && dst[dest_len])
		dest_len++;
	i = 0;
	while (src[i] && dest_len + i + 1 < dstsize)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (dest_len < dstsize)
		dst[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
