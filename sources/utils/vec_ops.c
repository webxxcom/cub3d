/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:46:53 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 23:36:53 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	vec2f_translate(t_vec2f const vec2f, float const dx, float const dy)
{
	return ((t_vec2f){
		.x = vec2f.x + dx,
		.y = vec2f.y + dy
	});
}

t_vec2f	vec2f_normalize(t_vec2f const vec2f)
{
	const double	magnitude = sqrt(vec2f.x * vec2f.x + vec2f.y * vec2f.y);

	if (magnitude == 0)
		return (vec2f_construct(0, 0));
	return (vec2f_construct(vec2f.x / magnitude, vec2f.y / magnitude));
}
