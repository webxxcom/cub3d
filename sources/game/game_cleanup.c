/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:41:34 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/28 22:17:56 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	decoration_cleanup(void *mlx, void *decor)
{
	t_decoration *const	tmp = decor;

	if (tmp->type != DECOR_WALL)
	{
		animation_cleanup(mlx, tmp->animation);
		tmp->animation = NULL;
	}
	else
		im_cleanup(mlx, tmp->texture);
}

static void map_cleanup(void *mlx, t_map *m)
{
	int32_t	j;

	j = 0;
	while (j < m->size.y)
	{
		if (m->tiles[j])
			free(m->tiles[j]);
		m->tiles[j] = NULL;
		++j;
	}
	if (m->tiles)
		free(m->tiles);
	m->tiles = NULL;
	j = 0;
	while (j < (int)array_size(&m->decorations))
	{
		decoration_cleanup(mlx, array_get(&m->decorations, j));
		++j;
	}
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

void game_cleanup(t_game *g)
{
	array_free(&g->input.pressed_keys);
	textures_cleanup(g);
	map_cleanup(g->mlx, &g->map);
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
