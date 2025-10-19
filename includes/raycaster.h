/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:10:01 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 17:09:22 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_vector_2d_float	t_vec2f;
typedef struct s_vector_2d_int		t_vec2i;

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

typedef enum e_texture_sides
{
	NORTH = 0,
	WEST,
	SOUTH,
	EAST
}	t_txtres_sides;

typedef struct s_texture_data
{
	float			dist;
	char			obs;
	t_vec2i			map_pos;
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
void		draw_vert_line(t_game *const g, int screen_x);
void		draw_floor_and_ceiling(t_game *g);
uint32_t	apply_all_lights_to_pixel(t_game *g, uint32_t col, float base_shade, t_vec2f obs_pos);
