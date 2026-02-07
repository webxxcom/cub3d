/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 12:12:10 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_player(uint32_t count)
{
	if (count == 0)
		return (error_found(ERROR_PLAYER_NOT_FOUND));
	if (count > 1)
		return (error_found(ERROR_MULTIPLE_PLAYERS_FOUND));
	return (0);
}

static int	validate_elements(t_game *game, char **map)
{
	uint32_t	player_count;
	int32_t		i;
	int32_t		j;

	player_count = 0;
	j = 0;
	while (j < game->map.size.y)
	{
		i = 0;
		while (i < game->map.size.x)
		{
			if (!is_valid_mapelement(map[j][i]))
				return (error_found(ERROR_UNKNOWN_ELEMENT_FOUND));
			if (map[j][i] == TILE_PLAYER_N || map[j][i] == TILE_PLAYER_S
				|| map[j][i] == TILE_PLAYER_E || map[j][i] == TILE_PLAYER_W)
			{
				game->map.tiles[j][i].type = '0';
				++player_count;
			}
			++i;
		}
		++j;
	}
	return (validate_player(player_count));
}

static int	validate_borders(t_game *game, char **map)
{
	int32_t const	w = game->map.size.x;
	int32_t const	h = game->map.size.y;
	int32_t			i;
	int32_t			j;
	bool			is_border;

	j = 0;
	while (j < game->map.size.y)
	{
		i = 0;
		while (i < game->map.size.x)
		{
			is_border = (j == 0 || j == h - 1 || i == 0 || i == w - 1);
			if (is_border && map[j][i] != TILE_VOID && map[j][i] != TILE_WALL)
				return error_found(ERROR_WALL);
			++i;
		}
		++j;
	}
	return (0);
}

static int	validate_walls(t_game *game, char **map)
{
	int32_t const	h = game->map.size.y;
	int32_t const	w = game->map.size.x;
	int32_t			i;
	int32_t			j;

	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			if (map[j][i] != ' ' && map[j][i] != '1')
			{
				if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
					return (error_found(ERROR_WALL));
				if (map[j - 1][i - 1] == ' ' || map[j - 1][i] == ' '
					|| map[j - 1][i + 1] == ' ' || map[j][i - 1] == ' '
					|| map[j][i + 1] == ' ' || map[j + 1][i - 1] == ' '
					|| map[j + 1][i] == ' ' || map[j + 1][i + 1] == ' ')
					return (error_found(ERROR_WALL));
			}
			++i;
		}
		++j;
	}
	return (0);
}

int	validate_map(t_game *game)
{
	char	**map;
	int		exit_status;

	exit_status = 0;
	map = get_chars_map(&game->map);
	exit_status = (validate_elements(game, map)
		|| validate_borders(game, map) || validate_walls(game, map));
	ft_free_matrix(map);
	return (exit_status);
}
