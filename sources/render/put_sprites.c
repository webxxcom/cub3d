/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:36:05 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/31 15:02:53 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	process_sprites(t_game *g, t_sprite *s1, t_sprite *s2)
{
	t_vec2f		d1 = vec2f_vtranslate(s1->pos, vec2f_neg(g->player.pos));
	t_vec2f		d2 = vec2f_vtranslate(s2->pos, vec2f_neg(g->player.pos));
	t_vec2f		dist = vec2f_construct(d1.x * d1.x + d1.y * d1.y, d2.x * d2.x + d2.y * d2.y);
	t_sprite	tmp;

	if (dist.x < dist.y)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
	}
	s1->dist = dist.x;
	s2->dist = dist.y;
}

static void	sort_sprites(t_game *g, t_array *sprites)
{
    size_t		i;
    size_t		j;
	t_sprite	*s1;
	t_sprite	*s2;

	i = 0;
	while (i < sprites->size)
	{
		j = i + 1;
		while (j < sprites->size)
		{
			s1 = &((t_sprite *)sprites->data)[i];
            s2 = &((t_sprite *)sprites->data)[j];
			process_sprites(g, s1, s2);
			++j;
		}
		++i;
	}
}


/**
 * To draw sprite on the screen we need to convert the sprite position
 * 	from world space to camera space and then to screen_space:
 * 			World space -> Camera space -> Screen space
 * Camera's direction and plane vectors form a 2D basis and we can express
 * 	any vector in this basis using inverse camera matrix.
 * 
 * Inverse matrix as per inverse of a square matrix:
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
	t_vec2f	sprite_relcam_pos = vec2f_construct(sprite->pos.x - g->cam.pos.x, sprite->pos.y - g->cam.pos.y);
	double const	inv_det = 1. / (g->cam.dir.y * g->cam.plane.x - g->cam.dir.x * g->cam.plane.y);
	t_vec2f			transform_vec = vec2f_construct(
		inv_det * (g->cam.dir.y * sprite_relcam_pos.x - g->cam.dir.x * sprite_relcam_pos.y),
		inv_det * (-g->cam.plane.y * sprite_relcam_pos.x + g->cam.plane.x * sprite_relcam_pos.y)
	);
	int		sprite_screen_x = g->w / 2 * (1 + transform_vec.x / transform_vec.y);
	int		sprite_height = abs((int)(g->h / transform_vec.y));
	int		draw_start_y = g->h / 2 - sprite_height / 2 + cam_get_pitch(&g->cam);
	if (draw_start_y < 0)
		draw_start_y = 0;
	int		draw_end_y = g->h / 2 + sprite_height / 2 + cam_get_pitch(&g->cam);
	if (draw_end_y + 1 > g->h)
		draw_end_y = g->h - 1;

	int	sprite_width = abs((int) (g->h / transform_vec.y));
	int	draw_start_x = sprite_screen_x - sprite_width / 2;
	if (draw_start_x < 0) draw_start_x = 0;
	int	draw_end_x = sprite_screen_x + sprite_width / 2;
	if (draw_end_x >= g->w) draw_end_x = g->w - 1;

	float const shade = 1 / sqrtf(sprite->dist);
	for(int stripe = draw_start_x; stripe < draw_end_x; ++stripe)
	{
		int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * sprite->texture->width / sprite_width) / 256);
		if (transform_vec.y > 0 && stripe > 0 && stripe < g->w && g->z_buffer[stripe] > sqrtf(sprite->dist))
		{
			for(int y = draw_start_y; y < draw_end_y; ++y)
			{
				float d = y - g->h / 2 - cam_get_pitch(&g->cam)  + sprite_height / 2;
				int texY = (d * sprite->texture->height) / sprite_height;
				uint32_t col = im_get_pixel(sprite->texture, tex_x, texY);
				if (col != TRANSPARENT_COLOR)
					im_set_pixel(g->buffer_image, stripe, y, im_scale_pixel(col, shade));
			}
		}
	}
}

void put_sprites(t_game *const g)
{
	t_sprite	*tmp;
	size_t			i;

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
