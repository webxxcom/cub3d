/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:49:54 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/12 15:04:13 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static void	draw_ceiling(t_game *g, int x, int y_end)
{
	int	y;

	y = 0;
	while (y < y_end)
		im_set_pixel(g->buffer_image, x, y++, 0xFFFFFFFF);
}

static void	draw_floor(t_game *g, int x, int y_start)
{
	while (y_start < g->h)
		im_set_pixel(g->buffer_image, x, y_start++, 0x4CAF50);
}

static void	draw_wall(t_game *g, t_vec2i spos, int y_end, t_dda_res ddar)
{
	const int	line_h = g->h / ddar.dist;
	double		wall_x;
	double		step_y;
	int			tex_x;
	double		tex_posy;

	if (ddar.side == SOUTH || ddar.side == NORTH)
		wall_x = g->player.pos.x + ddar.ray_dir.x * ddar.dist;
	else
		wall_x = g->player.pos.y + ddar.ray_dir.y * ddar.dist;
	wall_x = wall_x - floor(wall_x);
	step_y = (double)g->cubes->walls[ddar.side]->height / line_h;
	tex_x = g->cubes->walls[ddar.side]->width * wall_x;
	if ((ddar.side == EAST || ddar.side == WEST) && ddar.ray_dir.x > 0)
		tex_x = g->cubes->walls[ddar.side]->width - tex_x - 1;
	if ((ddar.side == NORTH || ddar.side == SOUTH) && ddar.ray_dir.y < 0)
		tex_x = g->cubes->walls[ddar.side]->width - tex_x - 1;
	tex_posy = (spos.y - ((g->h / 2) - (line_h / 2) + g->cam.pitch)) * step_y;
	while (spos.y < y_end)
	{
		im_set_pixel(g->buffer_image,
			spos.x, spos.y++,
			im_get_pixel(g->cubes->walls[ddar.side], tex_x, tex_posy));
		tex_posy += step_y;
	}
}

void	draw_vert_line(t_game *const g, int screen_x, t_dda_res ddar)
{
	const int	line_h = g->h / ddar.dist;
	int			y_start;
	int			y_end;

	y_start = (g->h / 2) - (line_h / 2) + g->cam.pitch;
	if (y_start < 0)
		y_start = 0;
	y_end = (g->h / 2) + (line_h / 2) + g->cam.pitch;
	if (y_end >= g->h)
		y_end = g->h - 1;
	draw_ceiling(g, screen_x, y_start);
	draw_wall(g, vec2i_construct(screen_x, y_start), y_end, ddar);
	draw_floor(g, screen_x, y_end);
}
