/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:49:54 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 17:24:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static int	get_cube_type(char obs)
{
	if (obs - '0' - 1 <= 17)
		return (obs - '0' - 1);
	return (0);
}

uint32_t	apply_all_lights_to_pixel(t_game *g, uint32_t col, float base_shade, t_vec2f obs_pos)
{
	t_light	*light;
	size_t	i;
	float	light_bonus;
	uint32_t lit_col;

	i = 0;
	light_bonus = 0;
	while (i < 1)
	{
		light = array_get(&g->lights, i);
		t_vec2f	hit_vec = vec2f_construct(obs_pos.x, obs_pos.y);
		float dx = light->pos.x - hit_vec.x;
		float dy = light->pos.y - hit_vec.y;
		float dist2 = dx * dx + dy * dy;

		if (dist2 < light->intensity * light->intensity)
			light_bonus = light->strength / (1.0f + dist2);
		float r = (((col >> 16) & 0xFF) /  255.f) * fminf(1.0f, base_shade + ((float)((light->color >> 16) & 0xFF) / 255.f) * light_bonus);
		float g_col = (((col >> 8) & 0xFF) /  255.f) * fminf(1.0f, base_shade + ((float)((light->color >> 8) & 0xFF) / 255.f) * light_bonus);
		float b = (((col & 0xFF) / 255.f)) * fminf(1.0f, base_shade + ((float)(light->color & 0xFF) / 255.f) * light_bonus);
		lit_col = ((int)(r * 255) << 16) | ((int)(g_col * 255) << 8) | ((int)(b * 255));
		++i;
	}
	return (lit_col);
}

static void	draw_wall(t_game *g, t_vec2i spos, int y_end, t_obs_data obs_data, t_vec2f ray_dir)
{
	const int	line_h = g->h / obs_data.dist;
	double		wall_x;
	double		step_y;
	int			tex_x;
	double		tex_posy;
	t_image		*cube_side;

	t_entity	*ent = find_entity_at(g, obs_data.map_pos);
	if (ent)
		cube_side = animation_get_current_image(ent->anim);
	else
		cube_side = g->textures[g->cubes[get_cube_type(obs_data.obs)].walls_ind[obs_data.side]];
	
	if ((obs_data.side == EAST || obs_data.side == WEST))
		wall_x = g->player.pos.y + ray_dir.y * obs_data.dist;
	else
		wall_x = g->player.pos.x + ray_dir.x * obs_data.dist;
	wall_x = wall_x - floor(wall_x);
	step_y = (double)cube_side->height / line_h;
	tex_x = cube_side->width * wall_x;
	if ((obs_data.side == EAST || obs_data.side == WEST) && ray_dir.x > 0 && obs_data.obs != 'D' && obs_data.obs != 'O')
		tex_x = cube_side->width - tex_x - 1;
	if ((obs_data.side == NORTH || obs_data.side == SOUTH) && ray_dir.y < 0 && obs_data.obs != 'D' && obs_data.obs != 'O')
		tex_x = cube_side->width - tex_x - 1;
	tex_posy = (spos.y - ((g->h / 2) - (line_h / 2) + cam_get_pitch(&g->cam))) * step_y;
	float base_shade = 1 / obs_data.dist;
	while (spos.y < y_end)
	{
		uint32_t col = im_get_pixel(cube_side, tex_x, tex_posy);
		if (col != TRANSPARENT_COLOR)
		{
			uint32_t lit_col = apply_all_lights_to_pixel(g, col, base_shade,
				vec2f_construct(g->player.pos.x + ray_dir.x * obs_data.dist, g->player.pos.y + ray_dir.y * obs_data.dist));
			im_set_pixel(g->buffer_image,
				spos.x, spos.y,
				lit_col);
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
