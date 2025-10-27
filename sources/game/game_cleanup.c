/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:41:34 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 17:47:37 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void map_cleanup(t_map *m)
{
	int32_t	j;

	j = 0;
	while (j < m->size.y)
		free(m->tiles[j++]);
	free(m->tiles);
	array_free(&m->decorations);
}

 void	textures_cleanup(t_game *g)
{
	size_t	i;

	i = 0;
	while (g->textures[i])
		im_cleanup(g->mlx, g->textures[i++]);
	free(g->textures);
}

void game_cleanup(t_game *game)
{
	array_free(&game->input.pressed_keys);
	//textures_cleanup(game);
	map_cleanup(&game->map);
	free(game->rays);
	if (game->mlx && game->buffer_image)
	{
		if (game->buffer_image)
			im_cleanup(game->mlx, game->buffer_image);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
	}
}
