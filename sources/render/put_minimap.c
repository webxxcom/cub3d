/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/11 00:11:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel(t_game *g, int x, int y, int mapPosX, int mapPosY)
{
	t_minimap *const	mm = &g->minimap;

	if (g->map[mapPosY][mapPosX] != '0')
		im_set_pixel(g->buffer_image, x, y, mm->wcol);
	else
	 	im_set_pixel(g->buffer_image, x, y, mm->bgcol);
}

static void	draw_tile(t_game *g, int offx, int offy, int w, int h, int mapPosX, int mapPosY)
{
	int	i;
	int	j;

	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			draw_pixel(g, i + offx, j + offy, mapPosX, mapPosY);
			++i;
		}
		++j;	
	}
}

static void draw_line(t_game *g, double ox, double oy, double x, double y, uint32_t col)
{
	double dx = x - ox;
	double dy = y - oy;

	int steps = fabs(dx) < fabs(dy) ? fabs(dy) : fabs(dx);

	double stepX = dx / steps;
	double stepY = dy / steps;
	
	double i = ox;
	double j = oy;
	while (steps > 0)
	{
		im_set_pixel(g->buffer_image, i, j, col);
		i += stepX;
		j += stepY;
		--steps;
	}
}

static void	draw_player(t_game *g)
{
	const t_vec2f	scale = vec2f_construct(20 / (double)g->minimap.size.x, 15 / (double)g->minimap.size.y);
	t_vec2f 		ppos = vec2f_construct(
		g->player.pos.x / scale.x + g->minimap.pos.x,
		-g->player.pos.y / scale.y + g->minimap.pos.y
	);
	const double	R = g->player.radius - 3;
	int 			alpha;

	alpha = 0;
	while (alpha < 360)
	{
		double rad = ((double)alpha * M_PI) / 180.;
		t_vec2f end = vec2f_construct(R * cos(rad) + ppos.x, R * sin(rad) + ppos.y);
		draw_line(g, ppos.x, ppos.y, ceil(end.x), ceil(end.y), g->minimap.pcol);
		++alpha;
	}
}

void	put_minimap(t_game *g)
{
	t_minimap *const	mm = &g->minimap;
	const t_vec2i		tnum = vec2i_construct(20, 15);
	const t_vec2i		tsize = vec2i_construct(10, 10); 
	int					i;
	int					j;

	j = 0;
	while (j < tnum.y)
	{
		i = 0;
		while (i < tnum.x)
		{
			draw_tile(g,
				i * tsize.x + mm->pos.x,
				-(j * tsize.y + tsize.y) + mm->pos.y,
				tsize.x,
				tsize.y,
				i,
				j);
			++i;
		}
		++j;
	}
	draw_player(g);
}