/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:54:02 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/07 17:54:52 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	proceed_fractional_part(char *str)
{
	float	fract;
	float	divisor;

	divisor = 10.;
	fract = 0.;
	if (*str == '.')
	{
		++str;
		divisor = 10;
		while (*str >= '0' && *str <= '9')
		{
			fract += (*str - '0') / divisor;
			divisor *= 10;
			++str;
		}
	}
	return (fract);
}

float	ft_atof(char *str)
{
	float	result;
	int8_t	sign;

	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	result = 0.;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		++str;
	}
	return ((result + proceed_fractional_part(str)) * sign);
}
