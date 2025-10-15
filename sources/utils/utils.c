/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:40:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 16:50:35 by webxxcom         ###   ########.fr       */
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

inline float ft_minf(float a, float b)
{
	if (a < b)
		return a;
	return (b);
}
