/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:41:39 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:40 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *left, char *right)
{
	while (*left && *right && *left == *right)
	{
		++left;
		++right;
	}
	return (*left - *right);
}