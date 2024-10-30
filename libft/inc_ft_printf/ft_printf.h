/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:20:42 by jakubnencza       #+#    #+#             */
/*   Updated: 2024/03/21 17:27:25 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_dec_to_hex(unsigned int n, int lower, int *counter);
void	ft_print_pointer(void *ptr, int *counter, int index);
void	ft_handle_num(char c, int num, int *counter);
int		ft_get_num_size(int num, int is_unsigned);
void	ft_handle_string(char *temp, int *counter);
void	ft_putnbr_unsigned_fd(unsigned int n, int fd, int *counter);

#endif