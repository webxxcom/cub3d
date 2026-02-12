/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:41:34 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:08:31 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	decoration_cleanup(void *mlx, void *decor)
{
	t_decoration *const	tmp = decor;

	if (tmp->animation)
	{
		animation_cleanup(mlx, tmp->animation);
		tmp->animation = NULL;
	}
	if (tmp->texture_path)
		freenull(&tmp->texture_path);
	if (tmp->interact_text)
		freenull(&tmp->interact_text);
	if (tmp->looking_at_text)
		freenull(&tmp->looking_at_text);
}

void	map_cleanup(void *mlx, t_map *m)
{
	int32_t	j;

	j = 0;
	while (j < m->size.y)
	{
		if (m->tiles[j])
			freenull(&m->tiles[j]);
		m->tiles[j] = NULL;
		++j;
	}
	if (m->tiles)
		freenull(&m->tiles);
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

	if (!g->textures)
		return ;
	i = 0;
	while (g->textures[i])
		im_cleanup(g->mlx, g->textures[i++]);
	freenull(&g->textures);
}

void	paths_cleanup(t_game *g)
{
	if (g->paths.ceiling)
		freenull(&g->paths.ceiling);
	if (g->paths.floor)
		freenull(&g->paths.floor);
	if (g->paths.north)
		freenull(&g->paths.north);
	if (g->paths.west)
		freenull(&g->paths.west);
	if (g->paths.south)
		freenull(&g->paths.south);
	if (g->paths.east)
		freenull(&g->paths.east);
}

void	sprites_cleanup(t_game *g, t_array *sprites)
{
	t_sprite	*tmp;
	size_t		i;

	i = 0;
	while (i < array_size(sprites))
	{
		tmp = array_get(sprites, i);
		if (tmp->animation)
			animation_cleanup(g->mlx, tmp->animation);
		if (tmp->interact_text)
			free(tmp->interact_text);
		if (tmp->looking_at_text)
			free(tmp->looking_at_text);
		if (tmp->texture_path)
			free(tmp->texture_path);
		++i;
	}
	array_free(sprites);
}
