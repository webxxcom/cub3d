/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/09 23:35:30 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	load_textures(t_game *game)
// {
// 	int	height;
// 	int	width;

// 	game->textures.north = mlx_xpm_file_to_image(
// 			game->mlx, game->paths.north, &width, &height);
// 	game->textures.north = mlx_xpm_file_to_image(
// 			game->mlx, game->paths.north, &width, &height);
// 	game->textures.north = mlx_xpm_file_to_image(
// 			game->mlx, game->paths.north, &width, &height);
// 	game->textures.north = mlx_xpm_file_to_image(
// 			game->mlx, game->paths.north, &width, &height);
// 	if (!game->textures.north || !game->textures.south
// 		|| !game->textures.east || !game->textures.west)
// 		exit_game(ERROR_MLX_IMAGE, game);
// }

// static char	*get_texture_path(void)
// {
// 	char	*path;

// 	path = ft_get_next_line()
// }

// static void parse_textures(t_game *game, const char *map_file);
// {
// 	printf("NO ");
// 	while (!game->paths.north)
// 		game->paths.north = get_texture_path(void);
// }

static t_view	cam_init()
{
	return ((t_view){
		.plane = vec2f_construct(0, 0.66f),
		.dir = vec2f_construct(-1, 0),
		.sensitivity = 0.2f}
	);
}
#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define WALL_DENSITY 0.15
#include <time.h>
int generate_map(t_game *game)
{
	int y, x;

	srand(time(NULL)); // seed RNG once per run

	game->map = malloc(sizeof(char *) * (MAP_HEIGHT + 1));
	if (!game->map)
		return (1);

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		game->map[y] = malloc(MAP_WIDTH + 1);
		if (!game->map[y])
			return (1);

		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1)
				game->map[y][x] = '1'; // border walls
			else if ((double)rand() / RAND_MAX < WALL_DENSITY)
				game->map[y][x] = rand() % 4 + 1 + '0'; // random internal wall
			else
				game->map[y][x] = '0'; // empty space
		}
		game->map[y][MAP_WIDTH] = '\0';
	}
	game->map[MAP_HEIGHT] = NULL;
	return (0);
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_game(ERROR_MLX_INIT, game);
	game->win = mlx_new_window(game->mlx, game->w, game->h, "cub3D");
	if (!game->win)
		exit_game(ERROR_MLX_WIN, game);

	game->buffer_image = im_get_empty(game->mlx, game->w, game->h);
	mlx_loop_hook(game->mlx, main_loop, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_window, game->mlx);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_mouse_hide(game->mlx, game->win);
}

static t_player	player_init()
{
	return ((t_player){
		.pos = vec2f_construct(5, 5), // ! POS IS HARDCODED
		.speed = 4.f,
		.radius = 0.2f
	});
}

static void	init_game(t_game *game)
{
	game->w = 1000;
	game->h = 650;
	game->cam = cam_init();
	
	
	// ! Hard code REVISE
	generate_map(game);
	game->player = player_init();
}

static void game_cleanup(t_game *game)
{
	im_cleanup(game->mlx, game->buffer_image);
	ft_lst_free(game->pressedKeys);
	ft_free_matrix(game->map);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
}

void	start_game(t_game *game, const char *filename)
{
	(void)filename;
	ft_memset(game, 0, sizeof(*game));
	//parse_textures(game, filename);
	//parse_map(game, filename);
	init_game(game);
	init_mlx(game);
	//load_textures(game);
	// int	i = 0;
	// while (game->map[i])
	// {
	// 	printf("%s\n", game->map[i]);
	// 	++i;
	// }
	game->lastTime = get_time_in_ms();
	mlx_loop(game->mlx);
	game_cleanup(game);
}
