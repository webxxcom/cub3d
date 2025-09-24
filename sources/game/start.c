/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/09/24 16:06:16 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	load_textures(t_game *game)
// {
// 	int	height;
// 	int	width;

// 	game->textures.north = mlx_xpm_file_to_image(
// 			game->mlx, "textures/floor.xpm", &width, &height);
// 	if (!game->textures.floor || !game->textures.wall
// 		|| !game->textures.collectible || !game->textures.exit
// 		|| !game->textures.player)
// 	{
// 		printf("Error: Failed to load images\n");
// 		exit_game(game, NULL);
// 	}
// }

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_game(ERROR_MLX_INIT, game);
	game->win = mlx_new_window(game->mlx, game->map.width * 10,
			game->map.height * 10, "cub3D");
	if (!game->win)
		exit_game(ERROR_MLX_WIN, game);
}

void	start_game(t_game *game, const char *filename)
{
	ft_memset(game, 0, sizeof(*game));
	parse_map(game, filename);
	init_mlx(game);
	int	i = 0;
	while (game->map.grid[i])
	{
		printf("%s\n", game->map.grid[i]);
		++i;
	}
	// render_map(game);
}