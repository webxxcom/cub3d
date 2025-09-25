/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/09/25 15:35:42 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_textures(t_game *game)
{
	int	height;
	int	width;

	game->textures.north = mlx_xpm_file_to_image(
			game->mlx, game->paths.north, &width, &height);
	game->textures.north = mlx_xpm_file_to_image(
			game->mlx, game->paths.north, &width, &height);
	game->textures.north = mlx_xpm_file_to_image(
			game->mlx, game->paths.north, &width, &height);
	game->textures.north = mlx_xpm_file_to_image(
			game->mlx, game->paths.north, &width, &height);
	if (!game->textures.north || !game->textures.south
		|| !game->textures.east || !game->textures.west)
		exit_game(ERROR_MLX_IMAGE, game);
}

static char	*get_texture_path(void)
{
	char	*path;

	path = ft_get_next_line()
}

static void parse_textures(t_game *game, const char *map_file);
{
	printf("NO ");
	while (!game->paths.north)
		game->paths.north = get_texture_path(void);
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_game(ERROR_MLX_INIT, game);
	game->win = mlx_new_window(game->mlx, 1000, 1000, "cub3D");
	if (!game->win)
		exit_game(ERROR_MLX_WIN, game);
}

void	start_game(t_game *game, const char *filename)
{
	ft_memset(game, 0, sizeof(*game));
	parse_textures(game filename);
	parse_map(game, filename);
	init_mlx(game);
	load_textures(game);
	int	i = 0;
	while (game->map[i])
	{
		printf("%s\n", game->map[i]);
		++i;
	}
	// render_map(game);
}
