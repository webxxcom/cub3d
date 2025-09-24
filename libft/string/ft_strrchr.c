/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:36:41 by phutran           #+#    #+#             */
/*   Updated: 2025/08/05 17:52:56 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	const char	*res;

	res = NULL;
	while (*str)
	{
		if (*str == (char)ch)
			res = str;
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return ((char *)res);
}
