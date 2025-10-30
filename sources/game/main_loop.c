/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 22:41:52 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	update_animations(t_game *g)
{
	t_decoration	*tmp;
	size_t			i;

	i = 0;
	while (i < array_size(&g->map.decorations))
	{
		tmp = array_get(&g->map.decorations, i);
		if (!tmp)
			continue ;
		if (tmp->update)
			tmp->update(g, tmp);
		++i;
	}
}

// Bezier curve is defined as B(t) = (1 - t)^2P0 + 2(1- t)tP1 + t^2P2
static t_vec2f bezier_quad(t_vec2f p0, t_vec2f p1, t_vec2f p2, float t)
{
	float const	u = 1.f - t;
	t_vec2f		res;
	
	res.x = u*u*p0.x + 2*u*t*p1.x + t*t*p2.x;
	res.y = u*u*p0.y + 2*u*t*p1.y + t*t*p2.y;
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

void update_cutscene(t_game *g, size_t idx)
{
	t_cutscene *const	cs = array_get(&g->cutscenes, idx);
	uint64_t const		now = get_time_in_ms();
	float const			dt = (now - cs->dtime) / 1000.f;
	t_vec2f				to_player_dir;
	
	if (!cs->is_going)
		return;
	cs->dtime = now;
	cs->lerp_t += dt * cs->speed;
	if (cs->lerp_t > 1.f)
		cs->lerp_t = 1.f;
	g->cam.pos = bezier_quad(cs->curve.p0, cs->curve.p1, cs->curve.p2, cs->lerp_t);
	to_player_dir = vec2f_normalize(vec2f_vtranslate(g->player.pos, vec2f_neg(g->cam.pos)));
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

int	main_loop(t_game *g)
{
	g->player.speed = g->player.base_speed;
	process_dtime(g);
	update_animations(g);
	repetition_handle(g);
	update_cutscene(g, 0);
	game_render(g);
	return (1);
}
