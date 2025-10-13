/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:10:01 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/13 22:11:30 by webxxcom         ###   ########.fr       */
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

typedef struct s_dda_res
{
	float			dist;
	t_vec2i			map_pos;
	t_vec2f			ray_dir;
	t_txtres_sides	side;
}	t_dda_res;

t_dda_d		get_dda_start_data(t_game *const g, int const screen_x);
t_dda_res	perform_dda(t_game *const g, double const screen_x);
void		draw_vert_line(t_game *const g, int screen_x, t_dda_res ddar);
