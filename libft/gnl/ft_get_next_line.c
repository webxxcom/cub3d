/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:53:57 by phutran           #+#    #+#             */
/*   Updated: 2025/08/13 00:42:33 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_stash(char *stash, int fd)
{
	char	*buffer;
	char	*joined;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (TRUE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		joined = ft_strjoin(stash, buffer);
		free(stash);
		stash = joined;
		if (!stash)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

static char	*get_remainder(char *newline)
{
	if (!newline)
		return (NULL);
	if (*(newline + 1) == '\0')
		return (NULL);
	return (ft_strdup(newline + 1));
}

static char	*get_line(char *stash, char *newline)
{
	if (stash && !(*stash))
	{
		free(stash);
		return (NULL);
	}
	if (newline)
		*(newline + 1) = '\0';
	return (stash);
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[1024];
	char		*newline;
	char		*remainder;
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = get_stash(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	newline = ft_strchr(stash[fd], '\n');
	remainder = get_remainder(newline);
	line = get_line(stash[fd], newline);
	stash[fd] = remainder;
	return (line);
}
