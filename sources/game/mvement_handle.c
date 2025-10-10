/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvement_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:19:44 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 16:35:02 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_walkable(t_game *g, float const x, float const y)
{
	return (g->map[(int)y][(int)x] == '0');
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
	 		dir_vec.x * pl->speed * g->dtime,
	 		dir_vec.y * pl->speed * g->dtime
		);

	if (is_walkable(g, pl->pos.x + delta.x * pl->radius, pl->pos.y))
		pl->pos.x += delta.x; 
	if (is_walkable(g, pl->pos.x, pl->pos.y + delta.y * pl->radius))
		pl->pos.y += delta.y;
}

void	handle_movement(t_game *const g)
{
	const t_vec2f	plane_norm = vec2f_normalize(g->cam.plane);
	t_vec2f			mv_dir;

	mv_dir = vec2f_init();
	if (g->moving_keys[MOVING_FRWD])
		mv_dir = vec2f_vtranslate(mv_dir, g->cam.dir);
	if (g->moving_keys[MOVING_BCK])
		mv_dir = vec2f_vtranslate(mv_dir, vec2f_neg(g->cam.dir));
	if (g->moving_keys[MOVING_RGHT])
		mv_dir = vec2f_vtranslate(mv_dir, plane_norm);
	if (g->moving_keys[MOVING_LFT])
		mv_dir = vec2f_vtranslate(mv_dir, vec2f_neg(plane_norm));
	if (mv_dir.x != 0 || mv_dir.y != 0)
		move(g, vec2f_normalize(mv_dir));
}