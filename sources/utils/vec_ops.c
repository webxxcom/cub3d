/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:46:53 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 00:26:06 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline t_vec2f	vec2f_translate(t_vec2f const vec2f, float dx, float dy)
{
	return ((t_vec2f){
		.x = vec2f.x + dx,
		.y = vec2f.y + dy
	});
}

inline t_vec2f	vec2f_vtranslate(t_vec2f const left, t_vec2f const right)
{
	return ((t_vec2f){
		.x = left.x + right.x,
		.y = left.y + right.y
	});
}

inline t_vec2f	vec2f_normalize(t_vec2f const vec2f)
{
	const double	magnitude = sqrt(vec2f.x * vec2f.x + vec2f.y * vec2f.y);

	if (magnitude == 0)
		return (vec2f_construct(0, 0));
	return (vec2f_construct(vec2f.x / magnitude, vec2f.y / magnitude));
}

inline t_vec2f	vec2f_neg(t_vec2f const vec2f)
{
	return ((t_vec2f){
		.x = -vec2f.x,
		.y = -vec2f.y
	});
}

inline bool	vec2i_equals(t_vec2i left, t_vec2i right)
{
	return (left.x == right.x && left.y == right.y);
}
