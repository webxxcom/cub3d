/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:13:19 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 11:51:42 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str1, const char *set)
{
	size_t	start;
	size_t	end;

	if (!str1 || !set)
		return (NULL);
	start = 0;
	while (str1[start] && ft_strchr(set, str1[start]))
		start++;
	end = ft_strlen(str1);
	while (end > start && ft_strchr(set, str1[end - 1]))
		end--;
	return (ft_substr(str1, start, end - start));
}
