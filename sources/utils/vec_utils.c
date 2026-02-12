/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:51:01 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/06 14:29:28 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline t_vec2f	vec2f_init(void)
{
	return ((t_vec2f){.x = 0, .y = 0});
}

inline t_vec2i	vec2i_init(void)
{
	return ((t_vec2i){.x = 0, .y = 0});
}

inline t_vec2f	vec2f_construct(float x, float y)
{
	return ((t_vec2f){.x = x, .y = y});
}

inline t_vec2i	vec2i_construct(int x, int y)
{
	return ((t_vec2i){.x = x, .y = y});
}

inline bool	vec2f_equals(t_vec2f left, t_vec2f right)
{
	static const float	epsilon = 0.001f;

	return (left.x - right.x < epsilon && left.y - right.y < epsilon);
}
