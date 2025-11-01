/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:50:44 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 21:50:55 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	calculate_sprite_distances(t_game *g)
{
	t_vec2f		delta;
	t_sprite	*sprt;
	size_t		i;

	i = 0;
	while (i < array_size(&g->sprites))
	{
		sprt = array_get(&g->sprites, i);
		if (sprt)
		{
			delta.x = sprt->pos.x - g->player.pos.x;
			delta.y = sprt->pos.y - g->player.pos.y;
			sprt->dist = sqrt(delta.x * delta.x + delta.y * delta.y);
		}
		++i;
	}
}

inline void	sort_sprites(t_game *g, t_array *sprites)
{
	size_t		i;
	size_t		j;
	t_sprite	*s1;
	t_sprite	*s2;
	t_sprite	tmp;

	calculate_sprite_distances(g);
	i = 0;
	while (i < sprites->size)
	{
		j = i + 1;
		while (j < sprites->size)
		{
			s1 = &((t_sprite *)sprites->data)[i];
			s2 = &((t_sprite *)sprites->data)[j];
			if (s1->dist < s2->dist)
			{
				tmp = *s1;
				*s1 = *s2;
				*s2 = tmp;
			}
			++j;
		}
		++i;
	}
}
