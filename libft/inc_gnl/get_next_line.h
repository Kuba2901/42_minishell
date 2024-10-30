/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:43:23 by jakubnencza       #+#    #+#             */
/*   Updated: 2024/03/10 14:19:04 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr(const char *s, int c); // ok
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize); // ok
char	*ft_strjoin(char const *s1, char const *s2); // 
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_join_reassign(char *buffer, char *to_join);
char	*ft_get_line_from_buff(char *buff);
char	*ft_read_until_nl(int fd);
char	*get_next_line(int fd);

#endif
