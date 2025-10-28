/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_decorations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:09:37 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/28 22:26:07 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void load_door(t_game *g, t_decoration *door, t_tile *tile)
{
	tile->type = TILE_DOOR;
	tile->sides[0] = door;
	tile->sides[1] = door;
	tile->sides[2] = door;
	tile->sides[3] = door;
	door->animation = init_animation(g, door->texture_path);
	if (!door->animation)
	{
		printf("Texture was not loaded %s\n", door->texture_path);
		exit(1);
	}
	door->texture = animation_get_current_image(door->animation); // ! REVISE
	door->update = door_update;
	door->interact = door_interact;
}

static void load_light(t_game *g, t_decoration *light, t_tile *tile)
{
	tile->sides[light->direction] = light;
	light->animation = init_animation(g, light->texture_path);
	if (!light->animation)
	{
		printf("Texture was not loaded %s\n", light->texture_path);
		exit(1);
	}
	light->texture = animation_get_current_image(light->animation); // ! REVISE
	light->update = light_update;
	light->interact = light_interact;
}

void load_wall_decor(t_game *g, t_decoration *wall, t_tile *tile)
{
	(void)g;
	//wall->animation = init_animation(g, wall->texture_path);
	wall->texture = im_load_from_xpmfile(g->mlx, wall->texture_path);
	//	animation_get_current_image(wall->animation);
	tile->sides[wall->direction] = wall;
}

void load_decorations(t_game *g)
{
	t_decoration	*tmp;
	t_vec2i			pos;
	size_t			i;

	i = 0;
	while (i < array_size(&g->map.decorations))
	{
		tmp = array_get(&g->map.decorations, i);
		pos = tmp->pos;
		if (tmp->type == DECOR_DOOR)
			load_door(g, tmp, &g->map.tiles[pos.y][pos.x]);
		else if (tmp->type == DECOR_LIGHT)
			load_light(g, tmp, &g->map.tiles[pos.y][pos.x]);
		else
			load_wall_decor(g, tmp, &g->map.tiles[pos.y][pos.x]);
		++i;
		free(tmp->texture_path);
		tmp->texture_path = NULL;
	}
}
