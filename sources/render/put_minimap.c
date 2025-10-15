/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 22:58:14 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static void	draw_pixel(t_game *g, int x, int y, t_vec2i map_pos)
{
	t_minimap *const	mm = &g->minimap;
	char				tile;
	uint32_t			col;

	map_pos = vec2i_construct(map_pos.x, g->map.size.y - map_pos.y - 1);
	tile = g->map.tiles[map_pos.y][map_pos.x];
	if (tile == '0')
		col = mm->bgcol;
	else if (tile == 'D' || tile == 'O')
		col = mm->dcol;
	else
		col = mm->wcol;
	im_set_pixel(g->buffer_image, x, y, col);
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
	const float	max_distance = 3.f;
	float		ray_dist;
	t_dda_ray	*ray;
	int			screen_x;
	
	screen_x = 0;
	while (screen_x < g->w)
	{
		ray = g->rays + screen_x;
		if (ray->dist > max_distance)
			ray_dist = max_distance;
		else
			ray_dist = ray->dist;
		draw_line(g, ppos,
			vec2f_construct(
				ppos.x + ray->ray_dir.x * ray_dist * scale.x,
				ppos.y + ray->ray_dir.y * ray_dist * scale.y),
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

	draw_player_ray(g, ppos, scale);
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
