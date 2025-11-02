/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:36:05 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 17:49:05 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	init_startvals_bf(t_game *g, t_ps *ps, t_sprite *sprt)
{
	double	inv_det;

	ps->sprite_relcam_pos = vec2f_construct(
			sprt->pos.x - g->cam.pos.x, sprt->pos.y - g->cam.pos.y);
	inv_det = 1.
		/ (g->cam.dir.y * g->cam.plane.x - g->cam.dir.x * g->cam.plane.y);
	ps->transform_vec = vec2f_construct(
			inv_det * (g->cam.dir.y * ps->sprite_relcam_pos.x
				- g->cam.dir.x * ps->sprite_relcam_pos.y),
			inv_det * (-g->cam.plane.y * ps->sprite_relcam_pos.x
				+ g->cam.plane.x * ps->sprite_relcam_pos.y));
}

static inline void	init_startvals(t_game *g, t_ps *ps, t_sprite *sprt)
{
	init_startvals_bf(g, ps, sprt);
	ps->sprite_screen_x = g->w / 2
		* (1 + ps->transform_vec.x / ps->transform_vec.y);
	ps->sprite_size.y = abs((int)(g->h / ps->transform_vec.y));
	ps->draw_start.y = g->h / 2 - ps->sprite_size.y / 2
		+ cam_get_pitch(&g->cam);
	if (ps->draw_start.y < 0)
		ps->draw_start.y = 0;
	ps->draw_end.y = g->h / 2 + ps->sprite_size.y / 2 + cam_get_pitch(&g->cam);
	if (ps->draw_end.y + 1 > g->h)
		ps->draw_end.y = g->h - 1;
	ps->sprite_size.x = ps->sprite_size.y;
	ps->draw_start.x = ps->sprite_screen_x - ps->sprite_size.x / 2;
	if (ps->draw_start.x < 0)
		ps->draw_start.x = 0;
	ps->draw_end.x = ps->sprite_screen_x + ps->sprite_size.x / 2;
	if (ps->draw_end.x >= g->w)
		ps->draw_end.x = g->w - 1;
}

static void	draw_sprite_vertical_line(t_game *g, t_ps *ps, int32_t stripe)
{
	uint32_t	col;
	float		d;
	int32_t		y;

	ps->tex_pos.x = (int)((256 * (stripe
					- (-ps->sprite_size.x / 2 + ps->sprite_screen_x))
				* ps->sprt->texture->width / ps->sprite_size.x) / 256);
	if (ps->transform_vec.y > 0 && stripe > 0
		&& stripe < g->w && g->z_buffer[stripe] > ps->transform_vec.y)
	{
		y = ps->draw_start.y;
		while (y < ps->draw_end.y)
		{
			d = y - g->h / 2 - cam_get_pitch(&g->cam) + ps->sprite_size.y / 2;
			ps->tex_pos.y = (d * ps->sprt->texture->height) / ps->sprite_size.y;
			col = im_get_pixel(ps->sprt->texture, ps->tex_pos.x, ps->tex_pos.y);
			if (col != TRANSPARENT_COLOR)
				im_set_pixel(g->buffer_image, stripe, y,
					im_scale_pixel_rgbf(col, ps->lit_bonus));
			++y;
		}
	}
}

/**
 * To draw sprite on the screen we need to convert the sprite position
 * 	from world space to camera space and then to screen_space, i.e.
 * 			World space -> Camera space -> Screen space
 * Camera's direction and plane vectors form a 2D basis and we can express
 * 	any vector in this basis by multiplying any vactor by inverse camera matrix.
 * 
 * Inverse camera matrix as per inverse of a square matrix:
 * 
 * 		A = [a	b]
 * 			[c	d]
 * 
 * 		A^-1 =    1		[ d -b ]
 * 			  (ad - bc) [-c	 a ], hence
 * 
 * Camera basis matrix:
 * 			[ PlaneX	DirX ]
 * 			[ PlaneY	DirY ], so
 * 
 * Inverse Camera matrix:
 * 
 * 			1	 [ DirY		-DirX ]
 * 		  det(M) [-PlaneY	 PlaneX ],
 * 
 * 	where det(M) = DirY * PlaneX - PlaneY * DirX
 * 
 *  Eventually the transformed position will be obtained as
 * 
 * 		1	[ DirY	  -DirX	   ] [ SpriteXrel ]
 * 	   det	[-PlaneY   PlaneX  ] [ SpriteYrel ]
 */
static void	put_sprite(t_game *const g, t_sprite *sprite)
{
	int32_t	stripe;
	t_ps	ps;

	init_startvals(g, &ps, sprite);
	ps.lit_bonus = get_light_bonus(g, 1 / sprite->dist, sprite->pos);
	stripe = ps.draw_start.x;
	ps.sprt = sprite;
	while (stripe < ps.draw_end.x)
	{
		draw_sprite_vertical_line(g, &ps, stripe);
		++stripe;
	}
}

void	put_sprites(t_game *const g)
{
	t_sprite	*tmp;
	size_t		i;

	sort_sprites(g, &g->sprites);
	i = 0;
	while (i < array_size(&g->sprites))
	{
		tmp = array_get(&g->sprites, i);
		if (tmp)
			put_sprite(g, tmp);
		++i;
	}
}
