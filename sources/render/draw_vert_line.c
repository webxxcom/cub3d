/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:49:54 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/22 23:22:20 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_wall(t_game *g, t_vec2i spos, int y_end, t_obs_data obs_data, t_vec2f ray_dir)
{
	const int	line_h = g->h / obs_data.dist;
	double		wall_x;
	double		step_y;
	int			tex_x;
	double		tex_posy;
	t_image		*cube_side;
	t_image		*decor = NULL;

	t_decoration *tmp;
	for(size_t i = 0; i < array_size(&g->decorations); ++i)
	{
		tmp =array_get(&g->decorations, i); 
		if (vec2i_equals(tmp->pos, obs_data.map_pos) && tmp->direction == obs_data.side)
		{
			decor = tmp->texture;
			break;
		}
	}
	cube_side = g->textures[obs_data.side];
	if ((obs_data.side == EAST || obs_data.side == WEST))
		wall_x = g->player.pos.y + ray_dir.y * obs_data.dist;
	else
		wall_x = g->player.pos.x + ray_dir.x * obs_data.dist;
	wall_x = wall_x - floor(wall_x);
	step_y = (double)cube_side->height / line_h;
	tex_x = cube_side->width * wall_x;
	if ((obs_data.side == EAST || obs_data.side == WEST) && ray_dir.x > 0)
		tex_x = cube_side->width - tex_x - 1;
	if ((obs_data.side == NORTH || obs_data.side == SOUTH) && ray_dir.y < 0)
		tex_x = cube_side->width - tex_x - 1;
	tex_posy = (spos.y - ((g->h / 2) - (line_h / 2) + cam_get_pitch(&g->cam))) * step_y;
	//float base_shade = 1 / obs_data.dist;
	while (spos.y < y_end)
	{
		uint32_t col = im_get_pixel(cube_side, tex_x, tex_posy);
		if (col != TRANSPARENT_COLOR)
		{
			//uint32_t lit_col = compute_lit_color(&g->lights, colorf_from_uint(col), base_shade,
				//vec2f_construct(g->player.pos.x + ray_dir.x * obs_data.dist, g->player.pos.y + ray_dir.y * obs_data.dist));
			im_set_pixel(g->buffer_image,
				spos.x, spos.y,
				col);
		}
		if (decor)
		{
			col = im_get_pixel(decor, tex_x, tex_posy);
			if (col != TRANSPARENT_COLOR)
			{
				//uint32_t lit_col = compute_lit_color(&g->lights, colorf_from_uint(col), base_shade,
					//vec2f_construct(g->player.pos.x + ray_dir.x * obs_data.dist, g->player.pos.y + ray_dir.y * obs_data.dist));
				im_set_pixel(g->buffer_image,
					spos.x, spos.y,
					col);
			}
		}
		tex_posy += step_y;
		++spos.y;
	}
}

void	draw_vert_line(t_game *const g, int screen_x)
{
	int	i;

	i = g->rays[screen_x].count - 1;
	while (i >= 0)
	{
		const int	line_h = g->h / g->rays[screen_x].crossed_textures[i].dist;
		int			y_start;
		int			y_end;

		y_start = (g->h / 2) - (line_h / 2) + cam_get_pitch(&g->cam);
		if (y_start < 0)
			y_start = 0;
		y_end = (g->h / 2) + (line_h / 2) + cam_get_pitch(&g->cam);
		if (y_end >= g->h)
			y_end = g->h - 1;
		draw_wall(g, vec2i_construct(screen_x, y_start), y_end, g->rays[screen_x].crossed_textures[i], g->rays[screen_x].ray_dir);
		--i;
	}
}
