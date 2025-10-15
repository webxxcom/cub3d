/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 16:07:22 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static void	draw_pixel(t_game *g, int x, int y, t_vec2i map_pos)
{
	t_minimap *const	mm = &g->minimap;

	map_pos = vec2i_construct(map_pos.x, g->map.size.y - map_pos.y - 1);
	if (g->map.tiles[map_pos.y][map_pos.x] != '0')
		im_set_pixel(g->buffer_image, x, y, mm->wcol);
	else
		im_set_pixel(g->buffer_image, x, y, mm->bgcol);
}

static void	draw_tile(t_game *g, t_vec2i offset, t_vec2i tsize, t_vec2i map_pos)
{
	int	i;
	int	j;

	j = 0;
	while (j < tsize.y)
	{
		i = 0;
		while (i < tsize.x)
		{
			draw_pixel(g, i + offset.x, j + offset.y, map_pos);
			++i;
		}
		++j;
	}
}

static void	draw_player_ray(t_game *g, t_vec2f ppos, t_vec2f scale)
{
	t_dda_d dda_data;
	
	int screen_x = 0;
	while (screen_x < g->w)
	{
		double cameraX = 2 * screen_x / (double)g->w - 1;
		dda_data.ray_dir = vec2f_construct(
			g->cam.dir.x + g->cam.plane.x * cameraX, 
			g->cam.dir.y + g->cam.plane.y * cameraX);
		dda_data.map_pos = vec2i_construct(g->player.pos.x, g->player.pos.y);
		dda_data.unit_step = vec2f_construct(fabs(1 / dda_data.ray_dir.x), fabs(1 / dda_data.ray_dir.y));
		if (dda_data.ray_dir.x < 0)
		{
			dda_data.map_step.x = -1;
			dda_data.side_dist.x = (g->player.pos.x - (int)g->player.pos.x) * dda_data.unit_step.x;
		}
		else
		{
			dda_data.map_step.x = 1;
			dda_data.side_dist.x = ((int)g->player.pos.x + 1 - g->player.pos.x) * dda_data.unit_step.x;
		}
		if (dda_data.ray_dir.y < 0)
		{
			dda_data.map_step.y = -1;
			dda_data.side_dist.y = (g->player.pos.y - (int)g->player.pos.y) * dda_data.unit_step.y;
		}
		else
		{
			dda_data.map_step.y = 1;
			dda_data.side_dist.y = ((int)g->player.pos.y + 1 - g->player.pos.y) * dda_data.unit_step.y;
		}

		double dist;
		bool hit = false;
		while(!hit)
		{
			if (dda_data.side_dist.x < dda_data.side_dist.y)
			{
				dist = dda_data.side_dist.x;
				dda_data.map_pos.x += dda_data.map_step.x;
				dda_data.side_dist.x += dda_data.unit_step.x;
			}
			else
			{
				dist = dda_data.side_dist.y;
				dda_data.map_pos.y += dda_data.map_step.y;
				dda_data.side_dist.y += dda_data.unit_step.y;
			}
			if (g->map.tiles[dda_data.map_pos.y][dda_data.map_pos.x] != '0')
				hit = true;
		}
		draw_line(g, ppos,
			vec2f_construct(
				ppos.x + dda_data.ray_dir.x * dist * scale.x,
				ppos.y + dda_data.ray_dir.y * dist * scale.y),
			g->minimap.rcol);
		++screen_x;
	}
}

static void	draw_player(t_game *g)
{
	const t_vec2f	scale = vec2f_construct(
			(double)g->minimap.size.x / g->map.size.x,
			(double)g->minimap.size.y / g->map.size.y);
	const t_vec2f	ppos = vec2f_construct(
			round(g->player.pos.x * scale.x) + g->minimap.pos.x,
			g->player.pos.y * scale.y + g->minimap.pos.y - g->minimap.size.y);
	const double	r = g->player.radius - 4;
	int				alpha;
	double			rad;

	alpha = 0;
	while (alpha < 360)
	{
		rad = ((double)alpha * M_PI) / 180.;
		draw_line(g, ppos,
			vec2f_construct(
				ceil(r * cos(rad) + ppos.x),
				ceil(r * sin(rad) + ppos.y)),
			g->minimap.pcol);
		++alpha;
	}
	draw_player_ray(g, ppos, scale);
}

void	put_minimap(t_game *g)
{
	t_minimap *const	mm = &g->minimap;
	const t_vec2i		tnum = vec2i_construct(g->map.size.x, g->map.size.y);
	const t_vec2i		tsize = vec2i_construct(
			g->minimap.size.x / g->map.size.x,
			g->minimap.size.y / g->map.size.y);
	int					i;
	int					j;

	j = 0;
	while (j < tnum.y)
	{
		i = 0;
		while (i < tnum.x)
		{
			draw_tile(g,
				vec2i_construct(i * tsize.x + mm->pos.x,
					-(j * tsize.y + tsize.y) + mm->pos.y),
				tsize,
				vec2i_construct(i, j));
			++i;
		}
		++j;
	}
	draw_player(g);
}
