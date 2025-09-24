/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:32 by phutran           #+#    #+#             */
/*   Updated: 2025/07/11 14:14:46 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(const char *str)
{
	int	len;

	if (!str)
		return (ft_print_str("(null)"));
	len = 0;
	while (str[len])
		ft_print_ch(str[len++]);
	return (len);
}
