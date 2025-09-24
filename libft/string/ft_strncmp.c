/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:42:56 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 13:04:20 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *lhs, const char *rhs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && lhs[i] && rhs[i] && lhs[i] == rhs[i])
		i++;
	if (i == count)
		return (0);
	return ((unsigned char)lhs[i] - (unsigned char)rhs[i]);
}
