/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:50:16 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/17 13:20:55 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define degToRad(x) (x * 3.14 / 180.)

void	draw_sprite(t_game *g, t_sprite *s)
{
	t_vec2f	spos;

	spos = vec2f_construct(s->pos.x - g->player.pos.x, s->pos.y - g->player.pos.y);
	double invDet = 1. / (g->cam.plane.x * g->cam.dir.y - g->cam.dir.x * g->cam.plane.y);

	double transformX = invDet * (g->cam.dir.y * spos.x - g->cam.dir.x * spos.y);
	double transformY = invDet * (-g->cam.plane.y * spos.x + g->cam.plane.x * spos.y);

	int spriteScreenX = (int)((g->w/2) * (1 + transformX / transformY));
	int spriteHeight = abs((int)(g->h / transformY));
	int drawStartY = -spriteHeight / 2 + g->h / 2;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + g->h / 2;
	if(drawEndY >= g->h) drawEndY = g->h - 1;

	int spriteWidth = abs( (int) (g->h / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= g->w) drawEndX = g->w - 1;

	for(int i = drawStartX; i < drawEndX; ++i)
	{
		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
		  im_set_pixel(g->buffer_image, y, i, COLOR_CYAN);
        }
	}
}
