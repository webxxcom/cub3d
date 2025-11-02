/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:28:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 18:29:55 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline float	vec2f_dist2(t_vec2f v1, t_vec2f v2)
{
	t_vec2f	delta = vec2f_construct(v1.x - v2.x, v1.y - v2.y);

	return (sqrtf(delta.x * delta.x + delta.y * delta.y));
}
