/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:10:53 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 12:53:08 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *lhs, const void *rhs, size_t count)
{
	const unsigned char	*lptr;
	const unsigned char	*rptr;
	size_t				i;

	lptr = (const unsigned char *)lhs;
	rptr = (const unsigned char *)rhs;
	i = 0;
	while (i < count && lptr[i] == rptr[i])
		i++;
	if (i == count)
		return (0);
	return (lptr[i] - rptr[i]);
}
