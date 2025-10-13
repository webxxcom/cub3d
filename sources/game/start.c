/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/13 22:55:56 by webxxcom         ###   ########.fr       */
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
		.sensitivity = 0.0008f,
		.pitch = 0
	});
}

#pragma region REMOVE WHEN PARSING IMPLEMENTED // !

#include <time.h>
char	**generate_map(int *w, int *h)
{
	const int HEIGHT = 24;
	const char *fixed_map[] = {
		"888888888884464464644464",
		"800000000084000000000004",
		"803300000884000000000006",
		"800300000000000000000006",
		"803300000884000000000004",
		"800000000084000006660646",
		"888808888884444446000006",
		"777707777080808084040606",
		"770000007808080886000006",
		"700000000000000086000004",
		"700000000000000086060606",
		"770000007808080886460666",
		"777707777884068483330333",
		"222202222464006063000003",
		"220000022400000043000003",
		"200000002400000043000003",
		"100000001444446063300033",
		"200000002221222660050505",
		"220000022200022050500055",
		"200000002000002505050505",
		"100000000000000000000005",
		"200000002000002505050505",
		"220000022200022050500055",
		"222212222221222555555555"
	};
	char **tiles;
	int y;

	tiles = malloc(sizeof(char *) * (HEIGHT + 1));
	if (!tiles)
		return NULL;

	for (y = 0; y < HEIGHT; y++)
	{
		tiles[y] = strdup(fixed_map[y]);
		if (!tiles[y])
		{
			while (--y >= 0)
				free(tiles[y]);
			free(tiles);
			return NULL;
		}
	}
	tiles[HEIGHT] = NULL;

	*w = 28;
	*h = HEIGHT;
	return tiles;
}

static void	load_textures(t_game *g)
{
	static char	*floor_filename = "textures/floor.xpm";
	static char	*ceiling_filename = "textures/ceiling.xpm";
	static char 		*textures_files[2][4] = {
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
	i = 0;

	g->floor = im_load_from_xpmfile(g->mlx, floor_filename);
	if (!g->floor)
		printf("The %s texture was not loaded\n", floor_filename), exit(1);
	g->ceiling = im_load_from_xpmfile(g->mlx, ceiling_filename);
	if (!g->ceiling)
		printf("The %s texture was not loaded\n", ceiling_filename), exit(1);
}

#pragma endregion

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
		.pos = vec2f_construct(7, 3), // ! POS IS HARDCODED
		.speed = 3.f,
		.base_speed = 3.f,
		.sprint_speed = 6.f,
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

static t_input	init_input()
{
	t_input	res;

	ft_memset(&res, 0, sizeof (res));
	return (res);
}

static void	init_game(t_game *g, const char *filename)
{
	g->w = 1000;
	g->h = 650;
	g->cam = cam_init();
	g->show_dbg = false;
	g->input = init_input();
	g->map = init_map(filename);
	g->minimap = minimap_init(g);
	
	
	// ! Hard code REVISE
	g->player = player_init();
}

void game_cleanup(t_game *game)
{
	ft_lst_free(game->input.pressed_keys);
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
