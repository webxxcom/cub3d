/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvement_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:19:44 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:57:35 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_open_door(t_game *g, int const x, int const y)
{
	return (g->map.tiles[y][x].type == TILE_DOOR
		&& g->map.tiles[y][x].sides[0]->state == OPEN);
}

/*
 The tile is walkable if the coordinates are:
	1) Within the map boundaries
	2) The tile is either a floor or an open door
*/
static bool	is_walkable(t_game *g, int const x, int const y)
{
	return ((x >= 0 && y >= 0 && x < g->map.size.x && y < g->map.size.y)
		&& (g->map.tiles[y][x].type == TILE_FLOOR
		|| is_open_door(g, x, y)));
}

t_vec2i	get_signs(t_vec2f const dir_vec)
{
	int	x;
	int	y;

	if (dir_vec.x < 0)
		x = -1;
	else
		x = 1;
	if (dir_vec.y < 0)
		y = -1;
	else
		y = 1;
	return (vec2i_construct(x, y));
}

static void	move(t_game *const g, t_vec2f dir_vec)
{
	t_player *const	pl = &g->player;
	const t_vec2f	delta = vec2f_construct(
			dir_vec.x * g->dtime,
			dir_vec.y * g->dtime);

	cam_process_bob(&g->cam, g->player.speed, g->dtime);
	if (is_walkable(g, pl->pos.x + delta.x * pl->radius * 2, pl->pos.y))
		pl->pos.x += delta.x * pl->speed;
	if (is_walkable(g, pl->pos.x, pl->pos.y + delta.y * pl->radius * 2))
		pl->pos.y += delta.y * pl->speed;
}

void	handle_movement(t_game *const g)
{
	const t_vec2f	plane_norm = vec2f_normalize(g->cam.plane);
	t_vec2f			mv_dir;

	mv_dir = vec2f_init();
	if (g->input.moving_keys[MOVING_FRWD]
		|| g->input.moving_keys[MOVING_BCK]
		|| g->input.moving_keys[MOVING_RGHT]
		|| g->input.moving_keys[MOVING_LFT])
	{
		if (g->input.moving_keys[MOVING_FRWD])
			mv_dir = vec2f_vtranslate(mv_dir, g->cam.dir);
		if (g->input.moving_keys[MOVING_BCK])
			mv_dir = vec2f_vtranslate(mv_dir, vec2f_neg(g->cam.dir));
		if (g->input.moving_keys[MOVING_RGHT])
			mv_dir = vec2f_vtranslate(mv_dir, plane_norm);
		if (g->input.moving_keys[MOVING_LFT])
			mv_dir = vec2f_vtranslate(mv_dir, vec2f_neg(plane_norm));
		move(g, vec2f_normalize(mv_dir));
	}
	else
		g->cam.bob_phase *= 1 - g->dtime;
	g->cam.pos = g->player.pos;
}
