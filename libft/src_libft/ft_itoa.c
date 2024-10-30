/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:43:50 by jnenczak          #+#    #+#             */
/*   Updated: 2024/02/03 15:43:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(long n)
{
	int	size;

	size = 0;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void	copy_num(long n, char *dst)
{
	char	a;

	if (n == -2147483648)
	{
		*dst++ = '-';
		*dst++ = '2';
		copy_num(147483648, dst);
	}
	else if (n < 0)
	{
		*dst++ = '-';
		copy_num(-n, dst);
	}
	else if (n <= 9)
	{
		a = n + '0';
		*dst++ = a;
	}
	else
	{
		copy_num(n / 10, dst);
		copy_num(n % 10, dst + ft_get_size(n / 10));
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	ln;

	ln = (long)n;
	ret = (char *)malloc(sizeof(char) * (ft_get_size(n) + 1));
	if (ret == NULL)
		return (NULL);
	copy_num(ln, ret);
	ret[ft_get_size(n)] = '\0';
	return (ret);
}
