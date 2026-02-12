/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
/*   Updated: 2026/02/12 10:30:44 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_player(size_t count)
{
	if (count == 0)
		return (error_found(ERROR_PLAYER_NOT_FOUND));
	if (count > 1)
		return (error_found(ERROR_MULTIPLE_PLAYERS_FOUND));
	return (0);
}

static int	validate_elements(t_map *const map)
{
	size_t	player_count;
	int32_t	i;
	int32_t	j;

	player_count = 0;
	j = 0;
	while (j < map->size.y)
	{
		i = 0;
		while (i < map->size.x)
		{
			if (!is_valid_mapelement(map->tiles[j][i].type))
				return (error_found(ERROR_UNKNOWN_ELEMENT_FOUND));
			else if (is_player_tile(map->tiles[j][i].type))
			{
				map->tiles[j][i].type = TILE_FLOOR;
				++player_count;
			}
			++i;
		}
		++j;
	}
	return (validate_player(player_count));
}

static inline bool	is_incomplete_wall(t_map *const map, int32_t i, int32_t j)
{
	return ((map->tiles[j][i].type != TILE_VOID
		&& map->tiles[j][i].type != TILE_WALL) && (i == 0 || j == 0
			|| i == map->size.x - 1 || j == map->size.y - 1 || map->tiles[j
			- 1][i - 1].type == TILE_VOID || map->tiles[j
			- 1][i].type == TILE_VOID || map->tiles[j - 1][i
			+ 1].type == TILE_VOID || map->tiles[j][i - 1].type == TILE_VOID
			|| map->tiles[j][i + 1].type == TILE_VOID || map->tiles[j + 1][i
			- 1].type == TILE_VOID || map->tiles[j + 1][i].type == TILE_VOID
			|| map->tiles[j + 1][i + 1].type == TILE_VOID));
}

static int	validate_walls(t_map *const map)
{
	int32_t	i;
	int32_t	j;

	j = 0;
	while (j < map->size.y)
	{
		i = 0;
		while (i < map->size.x)
		{
			if (is_incomplete_wall(map, i, j))
				return (error_found(ERROR_WALL));
			++i;
		}
		++j;
	}
	return (0);
}

int	validate_map(t_game *const g)
{
	return (validate_elements(&g->map) || validate_walls(&g->map));
}
