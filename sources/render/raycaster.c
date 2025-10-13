/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:55:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/13 22:11:35 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

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

inline static void	move_by_x(t_dda_d *const dda, t_dda_res *const dda_res)
{
	dda_res->dist = dda->side_dist.x;
	dda_res->side = WEST;
	dda->map_pos.x += dda->map_step.x;
	dda->side_dist.x += dda->unit_step.x;
}

inline static void	move_by_y(t_dda_d *const dda, t_dda_res *const dda_res)
{
	dda_res->dist = dda->side_dist.y;
	dda_res->side = NORTH;
	dda->map_pos.y += dda->map_step.y;
	dda->side_dist.y += dda->unit_step.y;
}

t_dda_res	perform_dda(t_game *const g, double const screen_x)
{
	t_dda_d		dda;
	t_dda_res	dda_res;
	bool		hit;

	dda = get_dda_start_data(g, screen_x);
	hit = false;
	ft_memset(&dda_res, 0, sizeof (dda_res));
	dda_res.ray_dir = dda.ray_dir;
	while (!hit)
	{
		if (dda.side_dist.x < dda.side_dist.y)
			move_by_x(&dda, &dda_res);
		else
			move_by_y(&dda, &dda_res);
		if (g->map.tiles[dda.map_pos.y][dda.map_pos.x] != '0')
			hit = true;
	}
	if (dda.ray_dir.x < 0 && dda_res.side == WEST)
		dda_res.side = EAST;
	else if (dda.ray_dir.y < 0 && dda_res.side == NORTH)
		dda_res.side = SOUTH;
	dda_res.map_pos = dda.map_pos;
	return (dda_res);
}
