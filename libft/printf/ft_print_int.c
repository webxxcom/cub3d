/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:38 by phutran           #+#    #+#             */
/*   Updated: 2025/07/11 14:14:34 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_int(int num)
{
	long	num_long;
	int		len;

	num_long = num;
	len = 0;
	if (num_long < 0)
	{
		num_long = -num_long;
		len += ft_print_ch('-');
	}
	if (num_long > 9)
		len += ft_print_int(num_long / 10);
	len += ft_print_ch(num_long % 10 + '0');
	return (len);
}
