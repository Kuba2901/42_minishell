/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:21:41 by jakubnencza       #+#    #+#             */
/*   Updated: 2024/03/10 14:10:19 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_reassign(char *buffer, char *to_join)
{
	char	*ret;

	if (buffer != NULL && to_join == NULL)
	{
		ret = ft_strdup(buffer);
		free(buffer);
		return (ret);
	}
	if (buffer == NULL && to_join != NULL)
	{
		ret = ft_strdup(to_join);
		free(to_join);
		return (ret);
	}
	if (!buffer)
		return (NULL);
	ret = ft_strjoin(buffer, to_join);
	free(buffer);
	free(to_join);
	return (ret);
}

char	*ft_read_until_nl(int fd)
{
	unsigned int	rbytes;
	char			*temp;
	char			*ret;

	rbytes = 1;
	ret = NULL;
	while (rbytes > 0)
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			break ;
		rbytes = read(fd, temp, BUFFER_SIZE);
		if (!rbytes)
		{
			free(temp);
			break ;
		}
		temp[rbytes] = '\0';
		ret = ft_join_reassign(ret, temp);
		if (ft_strchr(ret, '\n'))
			break ;
	}
	return (ret);
}

char	*ft_get_line_from_buff(char *buff)
{
	char	*line;
	int		i;

	i = -1;
	if (!buff)
		return (NULL);
	while (buff[++i])
	{
		if (buff[i] == '\n')
			break ;
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buff, i + 2);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*mark = NULL;
	char		*read_buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	read_buff = ft_read_until_nl(fd);
	if (mark != NULL)
	{
		if (!read_buff)
		{
			read_buff = ft_strdup(mark);
			free(mark);
			mark = NULL;
		}
		else
			read_buff = ft_join_reassign(mark, read_buff);
	}
	line = ft_get_line_from_buff(read_buff);
	mark = ft_strdup(read_buff + ft_strlen(line));
	free(read_buff);
	return (line);
}
