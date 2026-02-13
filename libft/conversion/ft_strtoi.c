/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:48:14 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 11:23:32 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <errno.h>

static int	skip_all(const char **str, int *sign, char **endptr)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
	if (!ft_isdigit(**str))
	{
		if (endptr)
			*endptr = (char *)*str;
		return (1);
	}
	return (0);
}

int	return_min_max(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	return (INT_MIN);
}

int	ft_strtoi(const char *str, char **endptr)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 1;
	if (skip_all(&str, &sign, endptr))
		return (0);
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (result > (INT_MAX - digit) / 10)
		{
			errno = ERANGE;
			if (endptr)
				*endptr = (char *)str;
			return (return_min_max(sign));
		}
		result = result * 10 + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
