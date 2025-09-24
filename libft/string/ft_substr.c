/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:28:20 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 13:07:09 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int pos, size_t count)
{
	char	*substr;
	size_t	str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (str_len < pos)
		return (ft_strdup(""));
	if (str_len < (pos + count))
		count = str_len - pos;
	substr = malloc((count + 1) * sizeof(*substr));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, str + pos, count);
	substr[count] = '\0';
	return (substr);
}
