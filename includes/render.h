/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:54:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/31 13:37:03 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "cub3D.h"

typedef struct s_game	t_game;
typedef struct s_vector_2d_int t_vec2i;
typedef struct s_vector_2d_float t_vec2f;

void	game_render(t_game *game);
void	draw_line(t_image *image, t_vec2i start,
			t_vec2i end, uint32_t col);
void	draw_circle(t_image *image, t_vec2i center,
			int32_t radius, uint32_t col);
void	add_crossed_texture(t_game *g, t_dda_d *dda, t_obs_data *wall_data, t_dda_ray *dda_res);
t_dda_d	get_dda_start_data(t_game *const g, int const screen_x);
void	move_by_x(t_dda_d *const dda, t_obs_data *const walld);
void	move_by_y(t_dda_d *const dda, t_obs_data *const walld);
void	add_crossed_texture(t_game *g, t_dda_d *dda, t_obs_data *wall_data, t_dda_ray *dda_res);
void	put_sprites(t_game *const g);
void	put_minimap(t_game *g);

#endif