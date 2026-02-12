/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:39:50 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:58:08 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Bezier curve is defined as B(t) = (1 - t)^2P0 + 2(1- t)tP1 + t^2P2
static t_vec2f	bezier_quad(t_vec2f p0, t_vec2f p1, t_vec2f p2, float t)
{
	float const	u = 1.f - t;
	t_vec2f		res;

	res.x = u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x;
	res.y = u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y;
	return (res);
}

// LERP linear interpolation is defined as (1 - t)A + tB
static t_vec2f	lerp_interpolation(t_vec2f a, t_vec2f b, float t)
{
	t_vec2f	res;

	res.x = (1 - t) * a.x + t * b.x;
	res.y = (1 - t) * a.y + t * b.y;
	return (res);
}

void	cutscene_update(t_game *g, t_cutscene *cs)
{
	uint64_t const	now = get_time_in_ms();
	float const		dt = (now - cs->dtime) / 1000.f;
	t_vec2f			to_player_dir;

	cs->dtime = now;
	cs->lerp_t += dt * cs->speed;
	if (cs->lerp_t > 1.f)
		cs->lerp_t = 1.f;
	g->cam.pos = bezier_quad(cs->curve.p0, cs->curve.p1,
			cs->curve.p2, cs->lerp_t);
	to_player_dir = vec2f_normalize(
			vec2f_vtranslate(g->player.pos, vec2f_neg(g->cam.pos)));
	g->cam.dir = lerp_interpolation(to_player_dir, g->player.dir, cs->lerp_t);
	g->cam.dir = vec2f_normalize(g->cam.dir);
	g->cam.plane = cam_get_plane_vec(g->cam.dir);
	if (cs->lerp_t >= 1.f)
	{
		cs->is_going = false;
		g->state = GAME_STATE_ON;
		g->cam.pos = g->player.pos;
		g->cam.dir = g->player.dir;
		g->cam.plane = cam_get_plane_vec(g->cam.dir);
	}
}

static inline t_cutscene	init_start_cutscene(t_game *g)
{
	t_cutscene	res;

	ft_memset(&res, 0, sizeof (t_cutscene));
	res.speed = 0.1f;
	res.dtime = get_time_in_ms();
	res.is_going = false;
	res.curve.p0 = vec2f_construct(
			g->player.pos.x - 0.8f, g->player.pos.y - 9.f);
	res.curve.p1 = vec2f_construct(
			g->player.pos.x + 2.f, g->player.pos.y - 2.f);
	res.curve.p2 = g->player.pos;
	g->show_dbg = true;
	return (res);
}

void	cutscenes_init(t_game *g)
{
	t_cutscene	tmp;

	g->cutscenes = array_init(sizeof (t_cutscene));
	tmp = init_start_cutscene(g);
	array_push(&g->cutscenes, &tmp);
}
