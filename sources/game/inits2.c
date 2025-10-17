/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:59:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 00:34:17 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_sprite	*init_sprites(t_game *g)
{
	t_sprite *const	sp = ft_calloc(1, sizeof (t_sprite));

	(void)g;
	if (!sp)
		return (NULL);
	sp[0] = (t_sprite){.pos = vec2f_construct(1.5, 2)};
	return (sp);
}

static inline t_entity	init_door(t_game *g, int x, int y)
{
	t_entity	ent;

	ent = (t_entity){
		.pos = vec2i_construct(x, y),
		.type = 'D',
		.state = 0,
		.update = door_update,
		.interact = door_interact
	};
	ent.anim = init_animation(g->mlx,
			"textures/lab_metal_white_door_sprite.xpm");
	return (ent);
}

void	init_entities(t_game *g)
{
	t_entity	tmp;
	int32_t		i;
	int32_t		j;

	g->entities = array_init(sizeof (t_entity));
	j = 0;
	while (j < g->map.size.y)
	{
		i = 0;
		while (i < g->map.size.x)
		{
			if (g->map.tiles[j][i] == 'D')
			{
				tmp = init_door(g, i, j);
				array_push(&g->entities, &tmp);
			}
			++i;
		}
		++j;
	}
}
