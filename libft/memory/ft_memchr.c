/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:13:28 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 12:44:31 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	const unsigned char	*uc_ptr;
	size_t				i;

	uc_ptr = (const unsigned char *)ptr;
	i = 0;
	while (i < count)
	{
		if (uc_ptr[i] == (unsigned char)ch)
			return ((void *)&uc_ptr[i]);
		i++;
	}
	return (NULL);
}
