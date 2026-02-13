/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:41:39 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 11:28:50 by danslav1e        ###   ########.fr       */
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
