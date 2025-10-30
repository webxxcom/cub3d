/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:55:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/30 21:02:00 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_startvals(t_game *const game,
		t_vec2f const ray_dir, t_dda_d *dda_d)
{
	if (ray_dir.x < 0)
	{
		dda_d->map_step.x = -1;
		dda_d->side_dist.x = (game->cam.pos.x - (int)game->cam.pos.x)
			* dda_d->unit_step.x;
	}
	else
	{
		dda_d->map_step.x = 1;
		dda_d->side_dist.x = ((int)game->cam.pos.x + 1 - game->cam.pos.x)
			* dda_d->unit_step.x;
	}
	if (ray_dir.y < 0)
	{
		dda_d->map_step.y = -1;
		dda_d->side_dist.y = (game->cam.pos.y - (int)game->cam.pos.y)
			* dda_d->unit_step.y;
	}
	else
	{
		dda_d->map_step.y = 1;
		dda_d->side_dist.y = ((int)game->cam.pos.y + 1 - game->cam.pos.y)
			* dda_d->unit_step.y;
	}
}

t_dda_d	get_dda_start_data(t_game *const g, int const screen_x)
{
	const double	camera_x = 2 * screen_x / (double)g->w - 1;
	const t_vec2f	ray_dir = vec2f_construct(
			g->cam.dir.x + g->cam.plane.x * camera_x,
			g->cam.dir.y + g->cam.plane.y * camera_x);
	t_dda_d			dda_d;

	dda_d = (t_dda_d){
		.ray_dir = ray_dir,
		.unit_step
		= vec2f_construct(fabs(1. / ray_dir.x), fabs(1. / ray_dir.y)),
		.map_pos = vec2i_construct(g->cam.pos.x, g->cam.pos.y)
	};
	init_startvals(g, ray_dir, &dda_d);
	return (dda_d);
}

inline void	move_by_x(t_dda_d *const dda, t_obs_data *const walld)
{
	walld->dist = dda->side_dist.x;
	walld->side = WEST;
	dda->map_pos.x += dda->map_step.x;
	dda->side_dist.x += dda->unit_step.x;
}

inline void	move_by_y(t_dda_d *const dda, t_obs_data *const walld)
{
	walld->dist = dda->side_dist.y;
	walld->side = NORTH;
	dda->map_pos.y += dda->map_step.y;
	dda->side_dist.y += dda->unit_step.y;
}

inline void	add_crossed_texture(
		t_game *g, t_dda_d *dda, t_obs_data *wall_data, t_dda_ray *dda_res)
{
	const size_t	idx = dda_res->count++;

	dda_res->crossed_textures[idx].obs
		= g->map.tiles[dda->map_pos.y][dda->map_pos.x].type;
	dda_res->crossed_textures[idx].map_pos = dda->map_pos;
	dda_res->crossed_textures[idx].pos = vec2f_construct(
			g->cam.pos.x + dda_res->ray_dir.x * wall_data->dist,
			g->cam.pos.y + dda_res->ray_dir.y * wall_data->dist);
	dda_res->crossed_textures[idx].dist = wall_data->dist;
	dda_res->crossed_textures[idx].side = wall_data->side;
}
