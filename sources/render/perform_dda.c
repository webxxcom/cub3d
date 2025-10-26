/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:55:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/26 10:07:00 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_startvals(t_game *const game,
		t_vec2f const ray_dir, t_dda_d *dda_d)
{
	if (ray_dir.x < 0)
	{
		dda_d->map_step.x = -1;
		dda_d->side_dist.x = (game->player.pos.x - (int)game->player.pos.x)
			* dda_d->unit_step.x;
	}
	else
	{
		dda_d->map_step.x = 1;
		dda_d->side_dist.x = ((int)game->player.pos.x + 1 - game->player.pos.x)
			* dda_d->unit_step.x;
	}
	if (ray_dir.y < 0)
	{
		dda_d->map_step.y = -1;
		dda_d->side_dist.y = (game->player.pos.y - (int)game->player.pos.y)
			* dda_d->unit_step.y;
	}
	else
	{
		dda_d->map_step.y = 1;
		dda_d->side_dist.y = ((int)game->player.pos.y + 1 - game->player.pos.y)
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
		.map_pos = vec2i_construct(g->player.pos.x, g->player.pos.y)
	};
	init_startvals(g, ray_dir, &dda_d);
	return (dda_d);
}

inline static void	move_by_x(t_dda_d *const dda, t_obs_data *const walld)
{
	walld->dist = dda->side_dist.x;
	walld->side = WEST;
	dda->map_pos.x += dda->map_step.x;
	dda->side_dist.x += dda->unit_step.x;
}

inline static void	move_by_y(t_dda_d *const dda, t_obs_data *const walld)
{
	walld->dist = dda->side_dist.y;
	walld->side = NORTH;
	dda->map_pos.y += dda->map_step.y;
	dda->side_dist.y += dda->unit_step.y;
}

t_dda_ray	perform_dda(t_game *const g, double const screen_x)
{
	t_dda_d		dda;
	t_obs_data	wall_data;
	t_dda_ray	dda_res;
	bool		hit;

	dda = get_dda_start_data(g, screen_x);
	hit = false;
	ft_memset(&dda_res, 0, sizeof (dda_res));
	ft_memset(&wall_data, 0, sizeof (t_obs_data));
	dda_res.ray_dir = dda.ray_dir;
	while (!hit)
	{
		if (dda.side_dist.x < dda.side_dist.y)
			move_by_x(&dda, &wall_data);
		else
			move_by_y(&dda, &wall_data);
		// if (g->map.tiles[dda.map_pos.y][dda.map_pos.x] == 'O'
		// 	|| g->map.tiles[dda.map_pos.y][dda.map_pos.x] == 'D'
		// 	|| g->map.tiles[dda.map_pos.y][dda.map_pos.x] == 'E'
		// 	|| g->map.tiles[dda.map_pos.y][dda.map_pos.x] == '9'
		// 	|| g->map.tiles[dda.map_pos.y][dda.map_pos.x] == ':')
		// {
		// 	const size_t	idx = dda_res.count++;
		// 	dda_res.crossed_textures[idx].dist = wall_data.dist;
		// 	dda_res.crossed_textures[idx].side = wall_data.side;
		// 	dda_res.crossed_textures[idx].map_pos = dda.map_pos;
		// 	dda_res.crossed_textures[idx].obs = g->map.tiles[dda.map_pos.y][dda.map_pos.x];
		// }
		if (g->map.tiles[dda.map_pos.y][dda.map_pos.x] != '0')
			hit = true;
	}
	if (dda.ray_dir.x < 0 && wall_data.side == WEST)
		wall_data.side = EAST;
	else if (dda.ray_dir.y < 0 && wall_data.side == NORTH)
		wall_data.side = SOUTH;
	wall_data.obs = g->map.tiles[dda.map_pos.y][dda.map_pos.x];
	wall_data.map_pos = dda.map_pos;
	dda_res.crossed_textures[dda_res.count++] = wall_data;
	return (dda_res);
}
