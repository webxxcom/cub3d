/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 14:30:47 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel(t_game *g, int x, int y, t_vec2i map_pos)
{
	t_minimap *const	mm = &g->minimap;
	char				tile;
	uint32_t			col;

	tile = g->map.tiles[map_pos.y][map_pos.x].type;
	if (tile == '0')
		col = mm->bgcol;
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

static void	draw_player_ray(t_game *g, t_vec2i ppos, t_vec2f scale)
{
	const float	max_distance = 3.f;
	float		ray_dist;
	t_dda_ray	*ray;
	int			screen_x;

	screen_x = 0;
	while (screen_x < g->w)
	{
		ray = g->rays + screen_x;
		if (ray->crossed_textures[0].dist > max_distance)
			ray_dist = max_distance;
		else
			ray_dist = ray->crossed_textures[0].dist;
		draw_line(g->buffer_image, ppos,
			vec2i_construct(
				round(ppos.x + ray->ray_dir.x * ray_dist * scale.x),
				round(ppos.y + ray->ray_dir.y * ray_dist * scale.y)),
			g->minimap.rcol);
		++screen_x;
	}
}

void	draw_player(t_game *g)
{
	const t_vec2f	scale = vec2f_construct(
			(double)g->minimap.size.x / g->map.size.x,
			(double)g->minimap.size.y / g->map.size.y);
	const t_vec2i	ppos = vec2i_construct(
			round(g->player.pos.x * scale.x) + g->minimap.pos.x,
			round(g->player.pos.y * scale.y)
			+ g->minimap.pos.y);
	const double	r = g->player.radius - 4;

	draw_player_ray(g, ppos, scale);
	draw_circle(g->buffer_image, ppos, r, g->minimap.pcol);
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
					j * tsize.y + mm->pos.y),
				tsize,
				vec2i_construct(i, j));
			++i;
		}
		++j;
	}
	draw_player(g);
}
