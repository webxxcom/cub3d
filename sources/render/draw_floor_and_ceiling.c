/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:01:29 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:30:38 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	draw_textured_fac(
		t_game *g, t_fac *facd, t_vec2i tex_pos, int32_t x)
{
	t_colorf	lit_bonus;

	lit_bonus = get_light_bonus(g, facd->shade, facd->floor_pos);
	if (facd->floor_y < g->h)
	{
		im_set_pixel(g->buffer_image, x, facd->floor_y,
			im_scale_pixel_rgbf(im_get_pixel(g->textures[TEXTR_FLOOR],
					tex_pos.x, tex_pos.y),
				lit_bonus));
	}
	if (facd->ceiling_y > 0)
	{
		im_set_pixel(g->buffer_image, x, facd->ceiling_y,
			im_scale_pixel_rgbf(im_get_pixel(g->textures[TEXTR_CEILING],
					tex_pos.x, tex_pos.y),
				lit_bonus));
	}
}

static inline void	draw_horizontal_line(t_game *g, t_fac *facd)
{
	int32_t		x;
	t_vec2i		tex_pos;

	x = 0;
	while (x < g->w)
	{
		tex_pos = vec2i_construct(
				(int)(g->textures[TEXTR_FLOOR]->width
					* (facd->floor_pos.x - (int)facd->floor_pos.x))
				% g->textures[TEXTR_FLOOR]->width,
				(int)(g->textures[TEXTR_FLOOR]->height
					* (facd->floor_pos.y - (int)facd->floor_pos.y))
				% g->textures[TEXTR_FLOOR]->height
				);
		draw_textured_fac(g, facd, tex_pos, x);
		facd->floor_pos = vec2f_vtranslate(
				facd->floor_pos, facd->floorunitstep);
		++x;
	}
}

void	draw_floor_and_ceiling(t_game *g)
{
	t_fac	facd;

	facd.raydir1 = vec2f_construct(g->cam.dir.x - g->cam.plane.x,
			g->cam.dir.y - g->cam.plane.y);
	facd.raydir2 = vec2f_construct(g->cam.dir.x + g->cam.plane.x,
			g->cam.dir.y + g->cam.plane.y);
	facd.posz = 0.5 * g->h;
	facd.horizon = g->h / 2 + cam_get_pitch(&g->cam);
	facd.floor_y = facd.horizon + 1;
	facd.ceiling_y = facd.horizon + 1;
	while (facd.floor_y < g->h || facd.ceiling_y > 0)
	{
		facd.p = facd.floor_y - facd.horizon;
		facd.rowdist = facd.posz / facd.p;
		facd.floorunitstep = vec2f_construct(
				facd.rowdist * (facd.raydir2.x - facd.raydir1.x) / g->w,
				facd.rowdist * (facd.raydir2.y - facd.raydir1.y) / g->w);
		facd.floor_pos = vec2f_construct(
				g->cam.pos.x + facd.rowdist * facd.raydir1.x,
				g->cam.pos.y + facd.rowdist * facd.raydir1.y);
		facd.shade = 1 / facd.rowdist;
		draw_horizontal_line(g, &facd);
		++facd.floor_y;
		--facd.ceiling_y;
	}
}
