/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:37:31 by phutran           #+#    #+#             */
/*   Updated: 2025/07/11 14:14:51 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uint(unsigned int num)
{
	int	len;

	len = 0;
	if (num > 9)
		len += ft_print_uint(num / 10);
	len += ft_print_ch(num % 10 + '0');
	return (len);
}
