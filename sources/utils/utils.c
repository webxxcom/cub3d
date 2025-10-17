/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:40:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 00:21:39 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline void	toggle_bool(bool *flag)
{
	if (*flag == true)
		*flag = false;
	else
		*flag = true;
}

inline float	ft_minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

inline int32_t	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

inline int32_t	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
