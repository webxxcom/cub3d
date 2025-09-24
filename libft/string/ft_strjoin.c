/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:58:06 by phutran           #+#    #+#             */
/*   Updated: 2025/08/08 14:15:29 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*res;
	char	*joined;
	size_t	len;

	len = 0;
	if (str1)
		len += ft_strlen(str1);
	if (str2)
		len += ft_strlen(str2);
	joined = malloc((len + 1) * sizeof(*joined));
	if (!joined)
		return (NULL);
	res = joined;
	while (str1 && *str1)
		*joined++ = *str1++;
	while (str2 && *str2)
		*joined++ = *str2++;
	*joined = '\0';
	return (res);
}
