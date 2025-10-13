/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:49:54 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/13 22:16:48 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static int	get_cube_type(t_game *g, t_vec2i map_pos)
{
	return ((g->map.tiles[map_pos.y][map_pos.x] - '0') % 2);
}

static void	draw_wall(t_game *g, t_vec2i spos, int y_end, t_dda_res ddar)
{
	const int	line_h = g->h / ddar.dist;
	double		wall_x;
	double		step_y;
	int			tex_x;
	double		tex_posy;
	t_image		*cube_side = g->cubes[get_cube_type(g, ddar.map_pos)].walls[ddar.side];

	if (ddar.side == SOUTH || ddar.side == NORTH)
		wall_x = g->player.pos.x + ddar.ray_dir.x * ddar.dist;
	else
		wall_x = g->player.pos.y + ddar.ray_dir.y * ddar.dist;
	wall_x = wall_x - floor(wall_x);
	step_y = (double)cube_side->height / line_h;
	tex_x = cube_side->width * wall_x;
	if ((ddar.side == EAST || ddar.side == WEST) && ddar.ray_dir.x > 0)
		tex_x = cube_side->width - tex_x - 1;
	if ((ddar.side == NORTH || ddar.side == SOUTH) && ddar.ray_dir.y < 0)
		tex_x = cube_side->width - tex_x - 1;
	tex_posy = (spos.y - ((g->h / 2) - (line_h / 2) + g->cam.pitch)) * step_y;
	while (spos.y < y_end)
	{
		im_set_pixel(g->buffer_image,
			spos.x, spos.y++,
			im_get_pixel(cube_side, tex_x, tex_posy));
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
	draw_wall(g, vec2i_construct(screen_x, y_start), y_end, ddar);
}
