/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:53:57 by phutran           #+#    #+#             */
/*   Updated: 2026/02/12 11:24:14 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next_line(int fd)
{
	char	*buf;
	char	*ptr;
	int		n;

	buf = malloc(10000);
	if (fd < 0 || buf == NULL)
		return (NULL);
	ptr = buf;
	while (1)
	{
		n = read(fd, ptr, 1);
		if (n <= 0)
			break ;
		if (*ptr == '\n')
		{
			ptr++;
			break ;
		}
		ptr++;
	}
	*ptr = '\0';
	if (ptr == buf && n <= 0)
		return (free(buf), NULL);
	return (buf);
}
