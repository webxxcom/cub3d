/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:01:29 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 18:42:58 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

void	draw_floor_and_ceiling(t_game *g)
{
	const t_vec2f	rayDir1 = vec2f_construct(g->cam.dir.x - g->cam.plane.x, g->cam.dir.y - g->cam.plane.y);
	const t_vec2f	rayDir2 = vec2f_construct(g->cam.dir.x + g->cam.plane.x, g->cam.dir.y + g->cam.plane.y);
	int				floor_y;
	int				ceiling_y;
	int				x;
	const float		posZ = 0.5 * g->h;
	const int		horizon = g->h / 2 + cam_get_pitch(&g->cam);

	floor_y = horizon + 1;
	ceiling_y = horizon + 1;
	while (floor_y < g->h || ceiling_y > 0)
	{
		int p = floor_y - horizon;
		float rowDist = posZ / p;

		t_vec2f floorUnitStep = vec2f_construct(
			rowDist * (rayDir2.x - rayDir1.x) / g->w,
			rowDist * (rayDir2.y - rayDir1.y) / g->w
		);
		t_vec2f floor_pos = vec2f_construct(
			g->player.pos.x + rowDist * rayDir1.x,
			g->player.pos.y + rowDist * rayDir1.y
		);
		x = 0;
		float shade = 1 / rowDist;
		uint32_t col;
		while (x < g->w)
	 	{
	 		t_vec2i texPos = vec2i_construct(
	 			(int)(g->textures[TEXTR_FLOOR_CHESSED]->width * (floor_pos.x - (int)floor_pos.x)) & (g->textures[TEXTR_FLOOR_CHESSED]->width - 1),
	 			(int)(g->textures[TEXTR_FLOOR_CHESSED]->height * (floor_pos.y - (int)floor_pos.y)) & (g->textures[TEXTR_FLOOR_CHESSED]->height - 1)
	 		);
			if (floor_y < g->h)
			{
				col = im_get_pixel(g->textures[TEXTR_FLOOR_CHESSED], texPos.x, texPos.y);
				im_set_pixel(g->buffer_image, x, floor_y,
					apply_all_lights_to_pixel(&g->lights, colorf_from_uint(col), shade, floor_pos)
				);
			}
			if (ceiling_y > 0)
			{
				col = im_get_pixel(g->textures[TEXTR_CEILING_ANGLES6], texPos.x, texPos.y);
				im_set_pixel(g->buffer_image, x, ceiling_y,
					apply_all_lights_to_pixel(&g->lights, colorf_from_uint(col), shade, floor_pos));
			}

	 		floor_pos = vec2f_vtranslate(floor_pos, floorUnitStep);
	 		++x;
	 	}
	 	++floor_y;
		 --ceiling_y;
	}
}
