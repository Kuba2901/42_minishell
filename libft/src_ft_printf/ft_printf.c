/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:15:29 by jakubnencza       #+#    #+#             */
/*   Updated: 2024/03/21 17:28:21 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_unsigned_fd(unsigned int n, int fd, int *counter)
{
	char	a;

	if (n <= 9)
	{
		a = n + 48;
		ft_putchar_fd(a, fd);
		*counter += 1;
	}
	else
	{
		ft_putnbr_unsigned_fd(n / 10, fd, counter);
		ft_putnbr_unsigned_fd(n % 10, fd, counter);
	}
}

static void	ft_print_casual(const char **str, int *counter)
{
	while (**str != '%' && **str)
	{
		ft_putchar_fd(**str, 1);
		*str += 1;
		*counter += 1;
	}
}

static void	ft_handle_given(char c, int *counter, va_list args)
{
	char	*temp;

	if (c == '%')
	{
		ft_putchar_fd('%', FT_STDOUT);
		*counter += 1;
	}
	else if (c == 'c' || c == 'd' || c == 'i' \
		|| c == 'u' || c == 'x' || c == 'X')
		ft_handle_num(c, va_arg(args, int), counter);
	else if (c == 's')
	{
		temp = va_arg(args, char *);
		ft_handle_string(temp, counter);
	}
	else if (c == 'p')
		ft_print_pointer(va_arg(args, void *), counter, 0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	c;
	int		counter;

	counter = 0;
	va_start(args, str);
	while (*str)
	{
		ft_print_casual(&str, &counter);
		if (!*str)
			break ;
		str++;
		c = *str;
		ft_handle_given(c, &counter, args);
		str++;
	}
	va_end(args);
	return (counter);
}
