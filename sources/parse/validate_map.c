/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 21:38:49 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate_filename(t_game *game, const char *filename)
{
	char	*basename;
	int		len;

	basename = ft_strrchr(filename, '/');
	if (!basename)
		basename = (char *)filename;
	if (*basename == '/')
		basename++;
	len = ft_strlen(basename);
	if (len == 4 && !ft_strcmp(basename + len - 4, ".cub"))
		exit_game(ERROR_INVALID_FILE, game);
	if (len < 4 || ft_strcmp(basename + len - 4, ".cub"))
		exit_game(ERROR_FILE_EXTENSION, game);
}

static void	validate_elements(t_game *game, char **map)
{
	int		player_count;
	int32_t	i;
	int32_t	j;	

	player_count = 0;
	j = 0;
	while (j < game->map.size.y)
	{
		i = 0;
		while (i < game->map.size.x)
		{
			if (map[j][i] != '0' && map[j][i] != '1'
				&& map[j][i] != 'N' && map[j][i] != 'S'
				&& map[j][i] != 'E' && map[j][i] != 'W'
				&& map[j][i] != ' ' && map[j][i] != TILE_DOOR) // ! SOMETHING
			{
				exit_game(ERROR_UNKNOWN_ELEMENT_FOUND, game);
			}
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
			{
				map[j][i] = '0';
				++player_count;
			}
			++i;
		}
		++j;
	}
	if (player_count == 0)
		exit_game(ERROR_PLAYER_NOT_FOUND, game);
	if (player_count > 1)
		exit_game(ERROR_MULTIPLE_PLAYERS_FOUND, game);
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
	int32_t	const	w = game->map.size.x;
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

char **get_chars_map(t_map *map)
{
	char	**map_chars;
	int32_t	i;
	int32_t	j;

	map_chars = ft_calloc(map->size.y + 1, sizeof (char *));
	j = 0;
	while (j < map->size.y)
	{
		map_chars[j] = ft_calloc(map->size.x, sizeof (char));
		i = 0;
		while (i < map->size.x)
		{
			map_chars[j][i] = map->tiles[j][i].type;
			++i;
		}
		++j;
	}
	map_chars[j] = NULL;
	return (map_chars);
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
