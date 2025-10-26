/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 11:16:17 by webxxcom         ###   ########.fr       */
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
	if (len == 4 && !ft_strncmp(basename + len - 4, ".cub", 4))
		exit_game(ERROR_INVALID_FILE, game);
	if (len < 4 || ft_strncmp(basename + len - 4, ".cub", 4))
		exit_game(ERROR_FILE_EXTENSION, game);
}

static void	validate_elements(t_game *game)
{
	int		player_count;
	int32_t	i;
	int32_t	j;	

	player_count = 0;
	j = 0;
	while (j < game->map.size.y)
	{
		i = 0;
		while (game->map.tiles[j][i])
		{
			if (game->map.tiles[j][i] != '0' && game->map.tiles[j][i] != '1'
				&& game->map.tiles[j][i] != 'N' && game->map.tiles[j][i] != 'S'
				&& game->map.tiles[j][i] != 'E' && game->map.tiles[j][i] != 'W'
				&& game->map.tiles[j][i] != ' ')
			{
				printf("%d, %d\n%s\n%c\n", i, j, game->map.tiles[j], game->map.tiles[j][i]);
				exit_game(ERROR_UNKNOWN_ELEMENT_FOUND, game);
			}
			if (game->map.tiles[j][i] == 'N' || game->map.tiles[j][i] == 'S'
				|| game->map.tiles[j][i] == 'E' || game->map.tiles[j][i] == 'W')
			{
				game->map.tiles[j][i] = '0';
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

static void	validate_borders(t_game *game)
{
	int32_t	i;
	int32_t	j;

	j = 0;
	while (j < game->map.size.y)
	{
		i = 0;
		while (game->map.tiles[j][i])
		{
			if (j == 0
				&& game->map.tiles[j][i] != ' ' && game->map.tiles[j][i] != '1')
				exit_game(ERROR_WALL, game);
			else if (!game->map.tiles[j + 1]
				&& game->map.tiles[j][i] != ' ' && game->map.tiles[j][i] != '1')
				exit_game(ERROR_WALL, game);
			else if (i == 0
				&& game->map.tiles[j][i] != ' ' && game->map.tiles[j][i] != '1')
				exit_game(ERROR_WALL, game);
			else if (!game->map.tiles[j][i + 1]
				&& game->map.tiles[j][i] != ' ' && game->map.tiles[j][i] != '1')
				exit_game(ERROR_WALL, game);
			++i;
		}
		++j;
	}
}

static void	validate_walls(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	int		len;

	map = game->map.tiles;
	i = -1;
	len = ft_strlen(map[0]);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1'
				&& (j > len - 1
				|| map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
				|| map[i - 1][j + 1] == ' ' || map[i + 1][j - 1] == ' '
				|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' '
				|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '
				|| map[i - 1][j + 1] == '\0' || map[i + 1][j + 1] == '\0'))
				exit_game(ERROR_WALL, game);
		}
		len = j;
	}
}

void	validate_map(t_game *game)
{
	validate_elements(game);
	validate_borders(game);
	validate_walls(game);
}
