/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:27:10 by phutran           #+#    #+#             */
/*   Updated: 2025/07/11 14:14:40 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(void *ptr)
{
	int	len;

	if (!ptr)
		return (ft_print_str("(nil)"));
	len = 0;
	len += ft_print_str("0x");
	len += ft_print_hex((uintptr_t)ptr, LOWERCASE);
	return (len);
}
