/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 15:10:06 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_player(t_game *game, int count)
{
	if (count == 0)
		exit_game(ERROR_PLAYER_NOT_FOUND, game);
	if (count > 1)
		exit_game(ERROR_MULTIPLE_PLAYERS_FOUND, game);
}

static void	validate_elements(t_game *game, char **map)
{
	int		player_count;
	int32_t	i;
	int32_t	j;	

	player_count = 0;
	j = -1;
	while (++j < game->map.size.y)
	{
		i = -1;
		while (++i < game->map.size.x)
		{
			if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != 'N'
				&& map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W'
				&& map[j][i] != ' ' && map[j][i] != TILE_DOOR)
				exit_game(ERROR_UNKNOWN_ELEMENT_FOUND, game);
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
			{
				map[j][i] = '0';
				++player_count;
			}
		}
	}
	validate_player(game, player_count);
}

static void	validate_borders(t_game *game, char **map)
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
			if (is_border && map[j][i] != ' ' && map[j][i] != '1')
				exit_game(ERROR_WALL, game);
			++i;
		}
		++j;
	}
}

static void	validate_walls(t_game *game, char **map)
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
					exit_game(ERROR_WALL, game);
				if (map[j - 1][i - 1] == ' ' || map[j - 1][i] == ' '
					|| map[j - 1][i + 1] == ' ' || map[j][i - 1] == ' '
					|| map[j][i + 1] == ' ' || map[j + 1][i - 1] == ' '
					|| map[j + 1][i] == ' ' || map[j + 1][i + 1] == ' ')
					exit_game(ERROR_WALL, game);
			}
			++i;
		}
		++j;
	}
}

void	validate_map(t_game *game)
{
	char	**map;

	map = get_chars_map(&game->map);
	validate_elements(game, map);
	validate_borders(game, map);
	validate_walls(game, map);
	ft_free_matrix(map);
}
