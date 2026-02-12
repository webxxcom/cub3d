/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:28:26 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:38:45 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline float	vec2f_dist2(t_vec2f v1, t_vec2f v2)
{
	t_vec2f	delta;

	delta = vec2f_construct(v1.x - v2.x, v1.y - v2.y);
	return (sqrtf(delta.x * delta.x + delta.y * delta.y));
}
