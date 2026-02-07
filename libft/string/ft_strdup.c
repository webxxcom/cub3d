/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:21:38 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 17:59:23 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*dup;
	size_t	i;

	if (!str1)
		return (NULL);
	dup = malloc((ft_strlen(str1) + 1) * sizeof(*dup));
	if (!dup)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		dup[i] = str1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
