/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/11 00:57:24 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel(t_game *g, int x, int y, t_vec2i map_pos)
{
	t_minimap *const	mm = &g->minimap;

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

static void	draw_line(t_game *g, t_vec2f start, t_vec2f end, uint32_t col)
{
	const t_vec2f	delta = vec2f_construct(
			end.x - start.x, end.y - start.y);
	t_vec2f			unit_step;
	int				steps;
	t_vec2f			current;

	if (fabs(delta.x) < fabs(delta.y))
		steps = fabs(delta.y);
	else
		steps = fabs(delta.x);
	unit_step = vec2f_construct(delta.x / steps, delta.y / steps);
	current = vec2f_construct(start.x, start.y);
	while (steps > 0)
	{
		im_set_pixel(g->buffer_image, current.x, current.y, col);
		current = vec2f_vtranslate(current, unit_step);
		--steps;
	}
}

static void	draw_player(t_game *g)
{
	const t_vec2f	scale = vec2f_construct(
			(double)g->minimap.size.x / g->map.size.x,
			(double)g->minimap.size.y / g->map.size.y);
	const t_vec2f	ppos = vec2f_construct(
			g->player.pos.x * scale.x + g->minimap.pos.x,
			-g->player.pos.y * scale.y + g->minimap.pos.y);
	const double	r = g->player.radius - 3;
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
