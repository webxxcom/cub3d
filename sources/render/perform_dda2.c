/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:57:13 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/31 14:58:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	intermediate_dda(
		t_game *g, t_dda_d *dda, t_obs_data *wall_data, t_dda_ray *dda_res)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (dda->side_dist.x < dda->side_dist.y)
			move_by_x(dda, wall_data);
		else
			move_by_y(dda, wall_data);
		if (g->map.tiles[dda->map_pos.y][dda->map_pos.x].type == TILE_DOOR)
			add_crossed_texture(g, dda, wall_data, dda_res);
		else if (g->map.tiles[dda->map_pos.y][dda->map_pos.x].type != '0')
			hit = true;
	}
	if (dda->ray_dir.x < 0 && wall_data->side == WEST)
		wall_data->side = EAST;
	else if (dda->ray_dir.y < 0 && wall_data->side == NORTH)
		wall_data->side = SOUTH;
	add_crossed_texture(g, dda, wall_data, dda_res);
}

t_dda_ray	perform_dda(t_game *const g, double const screen_x)
{
	t_dda_d		dda;
	t_obs_data	wall_data;
	t_dda_ray	dda_res;

	dda = get_dda_start_data(g, screen_x);
	ft_memset(&dda_res, 0, sizeof (dda_res));
	ft_memset(&wall_data, 0, sizeof (t_obs_data));
	dda_res.ray_dir = dda.ray_dir;
	intermediate_dda(g, &dda, &wall_data, &dda_res);
	return (dda_res);
}
