/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:48:14 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/07 16:29:19 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <errno.h>

static int skip_all(const char **str, int *sign, char **endptr)
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
			if (sign == 1)
				return (INT_MAX);
			return (INT_MIN);
		}
		(result = result * 10 + digit, str++);
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
