/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:41:34 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:00:29 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_cleanup(t_game *g)
{
	array_free(&g->input.pressed_keys);
	array_free(&g->lights);
	array_free(&g->cutscenes);
	sprites_cleanup(g, &g->sprites);
	textures_cleanup(g);
	map_cleanup(g->mlx, &g->map);
	paths_cleanup(g);
	if (g->z_buffer)
		freenull(&g->z_buffer);
	if (g->rays)
		free(g->rays);
	if (g->mlx && g->buffer_image)
	{
		if (g->buffer_image)
			im_cleanup(g->mlx, g->buffer_image);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}
