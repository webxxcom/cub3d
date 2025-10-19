/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lit_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:01:02 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 19:12:14 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	process_light(t_light *l, t_vec2f obs_pos, t_colorf *acc)
{
	float const	dx = l->pos.x - obs_pos.x;
	float const	dy = l->pos.y - obs_pos.y;
	float const	dist2 = dx * dx + dy * dy;
	float		light_bonus;

	if (dist2 < l->intensity * l->intensity)
	{
		light_bonus = l->strength / (1.f + dist2);
		acc->r += l->color.r * light_bonus;
		acc->g += l->color.g * light_bonus;
		acc->b += l->color.b * light_bonus;
	}
}

uint32_t	compute_lit_color(
		t_array *lights, t_colorf base, float base_shade, t_vec2f obs_pos)
{
	size_t		i;
	t_colorf	acc;

	i = 0;
	acc = colorf_init();
	while (i < array_size(lights))
	{
		process_light(array_get(lights, i), obs_pos, &acc);
		++i;
	}
	return (colorf_from_rgbf_to_uint(
			base.r * fminf(1.0f, base_shade + acc.r),
			base.g * fminf(1.0f, base_shade + acc.g),
			base.b * fminf(1.0f, base_shade + acc.b)
		)
	);
}
