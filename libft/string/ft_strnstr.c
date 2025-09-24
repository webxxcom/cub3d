/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:05:25 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 17:26:19 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strnstr(const char *str, const char *substr, size_t count)
{
	size_t	i;
	size_t	j;

	if (substr[0] == '\0')
		return (str);
	i = 0;
	while (i < count && str[i])
	{
		j = 0;
		while ((i + j) < count && substr[j] && str[i + j] == substr[j])
			j++;
		if (substr[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (NULL);
}
