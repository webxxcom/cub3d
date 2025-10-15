/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:54:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/15 23:59:24 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_game	t_game;
typedef struct s_vector_2d_int t_vec2i;
typedef struct s_vector_2d_float t_vec2f;

void	game_render(t_game *game);
void	draw_line(t_image *image, t_vec2f start_f,
			t_vec2f end_f, uint32_t col);
void	draw_circle(t_image *image, t_vec2i center,
			int32_t radius, uint32_t col);

#endif