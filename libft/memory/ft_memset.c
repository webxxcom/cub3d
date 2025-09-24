/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:46 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 12:44:56 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int ch, size_t count)
{
	unsigned char	*dest_ptr;
	size_t			i;

	dest_ptr = (unsigned char *)dest;
	i = 0;
	while (i < count)
	{
		dest_ptr[i] = (unsigned char)ch;
		i++;
	}
	return (dest);
}
