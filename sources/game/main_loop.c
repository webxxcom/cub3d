/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 21:31:22 by webxxcom         ###   ########.fr       */
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

float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

static t_vec2f bezier_quad(t_vec2f p0, t_vec2f p1, t_vec2f p2, float t)
{
    t_vec2f res;
    float u = 1.f - t;
    res.x = u*u*p0.x + 2*u*t*p1.x + t*t*p2.x;
    res.y = u*u*p0.y + 2*u*t*p1.y + t*t*p2.y;
    return res;
}
// Rebuild camera plane for raycasting
void update_cam_plane(t_game *g, float fov)
{
    // Plane is perpendicular to dir
    g->cam.plane.x = -g->cam.dir.y * fov;
    g->cam.plane.y =  g->cam.dir.x * fov;
}


void update_cutscene(t_game *g, size_t idx)
{
    t_cutscene *cs = array_get(&g->cutscenes, idx);
    if (!cs->is_going) return;

    uint64_t now = get_time_in_ms();
    float dt = (now - cs->dtime) / 1000.f;
    cs->dtime = now;

    cs->lerp_t += dt * cs->speed;
    if (cs->lerp_t > 1.f) cs->lerp_t = 1.f;

    // position along curved path
    t_vec2f cam_pos = bezier_quad(cs->curve.p0, cs->curve.p1, cs->curve.p2, cs->lerp_t);
    g->cam.pos = cam_pos;

    // direction blending
    float blend = cs->lerp_t;
    t_vec2f to_player = vec2f_vtranslate(g->player.pos, vec2f_neg(cam_pos));
    to_player = vec2f_normalize(to_player);
    g->cam.dir.x = (1-blend)*to_player.x + blend*g->player.dir.x;
    g->cam.dir.y = (1-blend)*to_player.y + blend*g->player.dir.y;
    g->cam.dir = vec2f_normalize(g->cam.dir);

    // rebuild plane
    update_cam_plane(g, 0.66f);

    if (cs->lerp_t >= 1.f)
    {
        cs->is_going = false;
        g->state = GAME_STATE_ON;
        g->cam.pos = g->player.pos;
        g->cam.dir = g->player.dir;
        update_cam_plane(g, 0.66f);
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
