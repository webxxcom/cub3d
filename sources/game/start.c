/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/11 00:34:53 by webxxcom         ###   ########.fr       */
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

static t_cam	cam_init()
{
	return ((t_cam){
		.plane = vec2f_construct(0, 0.66f),
		.dir = vec2f_construct(-1, 0),
		.sensitivity = 0.13f,
		.pitch = 0
	});
}
#include <time.h>
char	**generate_map(int *w, int *h)
{
	const int WIDTH = 20, HEIGHT = 15;
	const double WALL_DENSITY = 0.15;
	char	**tiles;
	int		y, x;

	srand(time(NULL));
	tiles = malloc(sizeof(char *) * (HEIGHT + 1));
	if (!tiles)
		return (NULL);
	for (y = 0; y < HEIGHT; y++)
	{
		tiles[y] = malloc(WIDTH + 1);
		if (!tiles[y])
			return (NULL);

		for (x = 0; x < WIDTH; x++)
		{
			if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1)
				tiles[y][x] = '1';
			else if ((double)rand() / RAND_MAX < WALL_DENSITY)
				tiles[y][x] = rand() % 4 + 1 + '0';
			else
				tiles[y][x] = '0';
		}
		tiles[y][WIDTH] = '\0';
	}
	tiles[HEIGHT] = NULL;
	*w = WIDTH;
	*h = HEIGHT;
	return (tiles);
}

static void	load_textures(t_game *g)
{
	static char *textures_files[2][4] = {
		{
			"textures/1.1.xpm",
			"textures/1.2.xpm",
			"textures/1.3.xpm",
			"textures/1.4.xpm",
		},
		{
			"textures/2.1.xpm",
			"textures/2.2.xpm",
			"textures/2.3.xpm",
			"textures/2.4.xpm",
		}
	};
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 4)
		{
			g->cubes[i].walls[j] = im_load_from_xpmfile(g->mlx, textures_files[i][j]);
			if (!g->cubes[i].walls[j])
			{
				printf("The texture %s was not loaded\n", textures_files[i][j]);
				while (--j)
					im_cleanup(g->mlx, g->cubes[i].walls[j]);
				game_cleanup(g);
				exit(1);
			}
			++j;
		}
		++i;
	}
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
	load_textures(game); // ! NOT CORRECT TEXTURE LOADING
	mlx_loop_hook(game->mlx, main_loop, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press_hook, game);
	mlx_key_hook(game->win, key_release_hook, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_window_hook, game->mlx);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move_hook, game);
	mlx_mouse_hide(game->mlx, game->win);
}

static t_player	player_init()
{
	return ((t_player){
		.pos = vec2f_construct(5, 5), // ! POS IS HARDCODED
		.speed = 3.f,
		.radius = 6.f 
	});
}

static t_map	init_map(const char *filename)
{
	t_map	res;

	(void)filename;
	res.tiles = generate_map(&res.size.x, &res.size.y);
	return (res);
}

static void	init_game(t_game *g, const char *filename)
{
	g->w = 1000;
	g->h = 650;
	g->cam = cam_init();
	g->show_dbg = false;
	ft_memset(g->moving_keys, 0, sizeof (g->moving_keys));
	g->minimap = minimap_init();
	g->map = init_map(filename);
	
	
	// ! Hard code REVISE
	g->player = player_init();
}

void game_cleanup(t_game *game)
{
	ft_lst_free(game->pressed_keys);
	ft_free_matrix(game->map.tiles);
	if (game->mlx && game->buffer_image)
		im_cleanup(game->mlx, game->buffer_image);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}

void	start_game(t_game *game, const char *filename)
{
	(void)filename;
	ft_memset(game, 0, sizeof(*game));
	//parse_textures(game, filename);
	//parse_map(game, filename);
	init_game(game, filename);
	init_mlx(game);
	//load_textures(game);
	// int	i = 0;
	// while (game->map[i])
	// {
	// 	printf("%s\n", game->map[i]);
	// 	++i;
	// }
	game->last_time = get_time_in_ms();
	mlx_loop(game->mlx);
	game_cleanup(game);
}
