/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:49:54 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 17:40:43 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline bool	decor_is_wall_decoration(t_decoration *decor)
{
	return (decor->type == DECOR_WALL);
}

static inline void	put_pixel_on_the_wall(t_game *g, t_dvl *dvl)
{
	uint32_t		col;
	t_colorf const	lit_bonus
		= get_light_bonus(g, dvl->base_shade, dvl->obs_data.pos);

	col = im_get_pixel(dvl->cube_side, dvl->tex_x, dvl->tex_posy);
	if (col != TRANSPARENT_COLOR)
	{
		im_set_pixel(g->buffer_image,
			dvl->screen_x, dvl->y_start, im_scale_pixel_rgbf(col, lit_bonus));
	}
	if (dvl->decor)
	{
		col = im_get_pixel(dvl->decor, dvl->tex_x, dvl->tex_posy);
		if (col != TRANSPARENT_COLOR)
		{
			im_set_pixel(g->buffer_image, dvl->screen_x,
				dvl->y_start, im_scale_pixel_rgbf(col, lit_bonus));
		}
	}
}

static void	draw_wall(t_game *g, t_dvl *dvl)
{
	dvl->step_y = (double)dvl->cube_side->height / dvl->line_h;
	dvl->tex_x = dvl->cube_side->width * dvl->wall_x;
	if (dvl->obs_data.side == EAST && dvl->ray_dir.x < 0)
		dvl->tex_x = dvl->cube_side->width - dvl->tex_x - 1;
	if (dvl->obs_data.side == NORTH && dvl->ray_dir.y > 0)
		dvl->tex_x = dvl->cube_side->width - dvl->tex_x - 1;
	dvl->tex_posy = (dvl->y_start - ((g->h / 2) - (dvl->line_h / 2)
				+ cam_get_pitch(&g->cam))) * dvl->step_y;
	dvl->base_shade = 1 / dvl->obs_data.dist;
	while (dvl->y_start < dvl->y_end)
	{
		put_pixel_on_the_wall(g, dvl);
		dvl->tex_posy += dvl->step_y;
		++dvl->y_start;
	}
}

static inline void	init_startvals(t_game *g, t_dvl *dvl, int32_t i)
{
	t_decoration	*tmp;

	dvl->line_h = g->h / g->rays[dvl->screen_x].crossed_textures[i].dist;
	dvl->y_start = (g->h / 2) - (dvl->line_h / 2) + cam_get_pitch(&g->cam);
	if (dvl->y_start < 0)
		dvl->y_start = 0;
	dvl->y_end = (g->h / 2) + (dvl->line_h / 2) + cam_get_pitch(&g->cam);
	if (dvl->y_end >= g->h)
		dvl->y_end = g->h - 1;
	dvl->obs_data = g->rays[dvl->screen_x].crossed_textures[i];
	dvl->ray_dir = g->rays[dvl->screen_x].ray_dir;
	tmp = g->map.tiles[dvl->obs_data.map_pos.y][dvl->obs_data.map_pos.x]
		.sides[dvl->obs_data.side];
	if (tmp && decor_is_wall_decoration(tmp))
		dvl->decor = tmp->texture;
	if (dvl->obs_data.obs == TILE_DOOR)
		dvl->cube_side = tmp->texture;
	else
		dvl->cube_side = g->textures[dvl->obs_data.side];
	if ((dvl->obs_data.side == EAST || dvl->obs_data.side == WEST))
		dvl->wall_x = g->cam.pos.y + dvl->ray_dir.y * dvl->obs_data.dist;
	else
		dvl->wall_x = g->cam.pos.x + dvl->ray_dir.x * dvl->obs_data.dist;
	dvl->wall_x = dvl->wall_x - (int)(dvl->wall_x);
}

void	draw_vert_line(t_game *const g, int screen_x, t_dda_ray rayd)
{
	t_dvl	dvl;
	int32_t	i;

	i = rayd.count - 1;
	ft_memset(&dvl, 0, sizeof (t_dvl));
	dvl.screen_x = screen_x;
	while (i >= 0)
	{
		init_startvals(g, &dvl, i);
		draw_wall(g, &dvl);
		dvl.decor = NULL;
		--i;
	}
}
