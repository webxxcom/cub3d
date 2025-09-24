/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:12 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 12:52:12 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int num)
{
	long	nbr;
	int		len;

	nbr = num;
	len = 0;
	if (nbr == 0)
		len++;
	else if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char	*res;
	long	nbr;
	int		len;

	len = ft_numlen(num);
	res = malloc((len + 1) * sizeof(*res));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	nbr = num;
	if (nbr == 0)
		res[0] = '0';
	else if (nbr < 0)
	{
		nbr = -nbr;
		res[0] = '-';
	}
	while (nbr > 0)
	{
		res[len--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (res);
}
