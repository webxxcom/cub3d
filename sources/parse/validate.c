// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   validate.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/22 14:48:04 by phutran           #+#    #+#             */
// /*   Updated: 2025/09/25 15:26:53 by phutran          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3D.h"

// void	validate_filename(t_game *game, const char *filename)
// {
// 	char	*basename;
// 	int		len;

// 	basename = ft_strrchr(filename, '/');
// 	if (!basename)
// 		basename = (char *)filename;
// 	if (*basename == '/')
// 		basename++;
// 	len = ft_strlen(basename);
// 	if (len == 4 && !ft_strncmp(basename + len - 4, ".cub", 4))
// 		exit_game(ERROR_INVALID_FILE, game);
// 	if (len < 4 || ft_strncmp(basename + len - 4, ".cub", 4))
// 		exit_game(ERROR_FILE_EXTENSION, game);
// }

// static void	validate_elements(t_game *game)
// {
// 	int	player_count;
// 	int	i;
// 	int	j;	

// 	player_count = 0;
// 	i = -1;
// 	while (game->map[++i])
// 	{
// 		j = -1;
// 		while (game->map[i][++j])
// 		{
// 			if (game->map[i][j] != '0' && game->map[i][j] != '1'
// 				&& game->map[i][j] != 'N' && game->map[i][j] != 'S'
// 				&& game->map[i][j] != 'E' && game->map[i][j] != 'W'
// 				&& game->map[i][j] != ' ')
// 				exit_game(ERROR_UNKNOWN_ELEMENT_FOUND, game);
// 			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
// 				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
// 				++player_count;
// 		}
// 	}
// 	if (player_count == 0)
// 		exit_game(ERROR_PLAYER_NOT_FOUND, game);
// 	if (player_count > 1)
// 		exit_game(ERROR_MULTIPLE_PLAYERS_FOUND, game);
// }

// static void	validate_borders(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (game->map[++i])
// 	{
// 		j = -1;
// 		while (game->map[i][++j])
// 		{
// 			if (i == 0
// 				&& game->map[i][j] != ' ' && game->map[i][j] != '1')
// 				exit_game(ERROR_WALL, game);
// 			else if (!game->map[i + 1]
// 				&& game->map[i][j] != ' ' && game->map[i][j] != '1')
// 				exit_game(ERROR_WALL, game);
// 			else if (j == 0
// 				&& game->map[i][j] != ' ' && game->map[i][j] != '1')
// 				exit_game(ERROR_WALL, game);
// 			else if (!game->map[i][j + 1]
// 				&& game->map[i][j] != ' ' && game->map[i][j] != '1')
// 				exit_game(ERROR_WALL, game);
// 		}
// 	}
// }

// static void	validate_walls(t_game *game)
// {
// 	char	**map;
// 	int		i;
// 	int		j;

// 	map = game->map;
// 	i = -1;
// 	while (map[++i])
// 	{
// 		j = -1;
// 		while (map[i][++j])
// 		{
// 			if (map[i][j] != ' ' && map[i][j] != '1'
// 				&& (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
// 				|| map[i - 1][j + 1] == ' ' || map[i + 1][j - 1] == ' '
// 				|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' '
// 				|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '
// 				|| map[i - 1][j + 1] == '\0' || map[i + 1][j + 1] == '\0'))
// 				exit_game(ERROR_WALL, game);
// 		}
// 	}
// }

// void	validate_map(t_game *game)
// {
// 	validate_elements(game);
// 	validate_borders(game);
// 	validate_walls(game);
// }
