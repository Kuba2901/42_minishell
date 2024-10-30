/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_con.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:16:22 by jakubnencza       #+#    #+#             */
/*   Updated: 2024/03/22 17:46:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_dec_to_hex(unsigned int n, int lower, int *counter)
{
	char	c;

	if (n <= 9)
	{
		ft_putchar_fd(n + '0', FT_STDOUT);
		*counter += 1;
	}
	else if (n < 16)
	{
		if (!lower)
			c = 'A' + n - 10;
		else
			c = 'a' + n - 10;
		ft_putchar_fd(c, FT_STDOUT);
		*counter += 1;
	}
	else
	{
		ft_dec_to_hex(n / 16, lower, counter);
		ft_dec_to_hex(n % 16, lower, counter);
	}
}

void	ft_print_pointer(void *ptr, int *counter, int index)
{
	uintptr_t	address;
	int			remainder;
	char		buffer[20];

	if (ptr == NULL)
	{
		ft_putstr_fd("0x0", FT_STDOUT);
		*counter += 3;
		return ;
	}
	address = (uintptr_t)ptr;
	while (address > 0)
	{
		remainder = address % 16;
		if (remainder < 10)
			buffer[index++] = '0' + remainder;
		else
			buffer[index++] = 'a' + remainder - 10;
		address /= 16;
	}
	buffer[index++] = 'x';
	buffer[index++] = '0';
	*counter += index;
	while (index > 0)
		ft_putchar_fd(buffer[--index], FT_STDOUT);
}

void	ft_handle_num(char c, int num, int *counter)
{
	unsigned int	converted;

	if (c == 'u')
	{
		converted = (unsigned int)num;
		ft_putnbr_unsigned_fd(converted, FT_STDOUT, counter);
	}
	else if (c == 'c')
	{
		ft_putchar_fd(num, FT_STDOUT);
		*counter += 1;
	}
	else if (c == 'x' || c == 'X')
		ft_dec_to_hex((unsigned int)num, c == 'x', counter);
	else
	{
		ft_putnbr_fd(num, FT_STDOUT);
		*counter += ft_get_num_size(num, 0);
	}
}

int	ft_get_num_size(int num, int is_unsigned)
{
	int	size;

	size = 0;
	if (!num)
		return (1);
	if (is_unsigned)
		num = (unsigned int)num;
	if (num < 0)
	{
		size++;
		num *= -1;
	}
	while (num)
	{
		size++;
		num /= 10;
	}
	return (size);
}

void	ft_handle_string(char *temp, int *counter)
{
	if (!(temp == NULL))
	{
		*counter += ft_strlen(temp);
		ft_putstr_fd(temp, FT_STDOUT);
	}
	else
	{
		ft_putstr_fd("(null)", FT_STDOUT);
		*counter += 6;
	}
}
