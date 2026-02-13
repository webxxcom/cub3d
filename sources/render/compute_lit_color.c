/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lit_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:01:02 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/13 14:35:26 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Light bonus is get using formula I = S / (d^2), where
 * 	S - is the light's strength and d - is the distance to the point.
 * To avoid division by zero we add small constant at denominator
 */
static inline t_colorf	process_light(t_light *l, t_vec2f obs_pos)
{
	float const	dx = l->pos.x - obs_pos.x;
	float const	dy = l->pos.y - obs_pos.y;
	float		light_bonus;
	float		is_active;
	t_colorf	res;

	res = colorf_init();
	light_bonus = l->strength / (1.f + dx * dx + dy * dy);
	is_active = light_bonus > 0.05f;
	res.r += l->color.r * light_bonus * is_active;
	res.g += l->color.g * light_bonus * is_active;
	res.b += l->color.b * light_bonus * is_active;
	return (res);
}

static inline t_colorf	compute_light_bonus(
		t_light *l, t_vec2f obs_pos, t_colorf base)
{
	t_colorf	acc;

	acc = process_light(l, obs_pos);
	return (colorf_from_rgbf(
			fminf(1.0f, base.r + acc.r),
			fminf(1.0f, base.g + acc.g),
			fminf(1.0f, base.b + acc.b)
		)
	);
}

t_colorf	get_light_bonus(t_game *g, float base_shade, t_vec2f obs_pos)
{
	size_t		i;
	t_colorf	lit_col;

	i = 0;
	lit_col = colorf_from_rgbf(base_shade, base_shade, base_shade);
	while (i < array_size(&g->lights))
	{
		lit_col = compute_light_bonus(array_get(&g->lights, i),
				obs_pos, lit_col);
		++i;
	}
	return (lit_col);
}
