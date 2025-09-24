/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:23:14 by phutran           #+#    #+#             */
/*   Updated: 2025/07/11 14:14:22 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long num, int letter_case)
{
	const char	*hex = "0123456789abcdef";
	int			len;

	if (UPPERCASE == letter_case)
		hex = "0123456789ABCDEF";
	len = 0;
	if (num > 15)
		len += ft_print_hex(num / 16, letter_case);
	len += ft_print_ch(hex[num % 16]);
	return (len);
}
