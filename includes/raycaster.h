/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:10:01 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 21:58:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

#include "cub3D.h"

typedef struct s_ray_step
{
	t_vec2f	pos;
	t_vec2f	step;
}	t_ray_step;

typedef struct s_dda_data
{
	t_vec2i	map_pos;
	t_vec2i	map_step;
	t_vec2f	unit_step;
	t_vec2f	side_dist;
	t_vec2f	ray_dir;
}	t_dda_d;

typedef struct s_obs_data
{
	float			dist;
	char			obs;
	t_vec2i			map_pos;
	t_vec2f			pos;
	t_txtres_sides	side;
}	t_obs_data;

typedef struct s_dda_ray
{
	t_vec2f			ray_dir;
	t_obs_data		crossed_textures[10];
	size_t			count;
}	t_dda_ray;

t_dda_d		get_dda_start_data(t_game *const g, int const screen_x);
t_dda_ray	perform_dda(t_game *const g, double const screen_x);
void		draw_vert_line(t_game *const g, int screen_x, t_dda_ray rayd);
void		draw_floor_and_ceiling(t_game *g);
void		sort_sprites(t_game *g, t_array *sprites);


// Helper structures to avoid norminette complains..

typedef struct s_fac
{
	t_vec2f	rayDir1;
	t_vec2f	rayDir2;
	int32_t	x;
	float	posZ;
	int		horizon;
	t_vec2f floorUnitStep;
	t_vec2f floor_pos;
	int		p;
	float	rowDist;
	int32_t	floor_y;
	int32_t	ceiling_y;
	float	shade;
}	t_fac;

typedef struct s_dvl
{
	int			screen_x;
	int32_t		line_h;
	int32_t		y_start;
	int32_t 	y_end;
	t_obs_data	obs_data;
	t_vec2f		ray_dir;
	double		wall_x;
	double		step_y;
	int			tex_x;
	double		tex_posy;
	t_image		*cube_side;
	t_image		*decor;
	float		base_shade;
}	t_dvl;

typedef struct s_put_sprite
{
	t_sprite	*sprt;
	t_vec2f		sprite_relcam_pos;
	t_vec2f		transform_vec;
	int32_t		sprite_screen_x;
	t_vec2f		sprite_size;
	t_vec2f		draw_start;
	t_vec2f		draw_end;
	t_vec2f		tex_pos;
	t_colorf	lit_bonus;
}	t_ps;

#endif