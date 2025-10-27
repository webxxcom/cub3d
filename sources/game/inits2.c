/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:59:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 14:31:41 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// t_sprite	*init_sprites(t_game *g)
// {
// 	t_sprite *const	sp = ft_calloc(1, sizeof (t_sprite));

// 	(void)g;
// 	if (!sp)
// 		return (NULL);
// 	sp[0] = (t_sprite){.pos = vec2f_construct(1.5, 2)};
// 	return (sp);
// }

// static inline t_entity	init_door(t_game *g, int x, int y, t_animation_types animation)
// {
// 	t_entity	ent;

// 	ent = (t_entity){
// 		.pos = vec2i_construct(x, y),
// 		.type = 'D',
// 		.state = 0,
// 		.update = door_update,
// 		.interact = door_interact
// 	};
// 	ent.anim = init_animation(g, animation);
// 	return (ent);
// }

// void	init_entities(t_game *g)
// {
// 	t_entity	tmp;
// 	int32_t		i;
// 	int32_t		j;

// 	g->entities = array_init(sizeof (t_entity));
// 	j = 0;
// 	while (j < g->map.size.y)
// 	{
// 		i = 0;
// 		while (i < g->map.size.x)
// 		{
// 			if (g->map.tiles[j][i] == 'D')
// 			{
// 				tmp = init_door(g, i, j, ANIM_DOOR_OPEN_CLOSE);
// 				array_push(&g->entities, &tmp);
// 			}
// 			else if (g->map.tiles[j][i] == 'E')
// 			{
// 				tmp = init_door(g, i, j, ANIM_LAB_METAL_GREY_TILES_HEXDOOR);
// 				array_push(&g->entities, &tmp);
// 			}
// 			++i;
// 		}
// 		++j;
// 	}
// }
