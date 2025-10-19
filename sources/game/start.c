/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/19 18:38:12 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

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
static void	load_textures(t_game *g)
{
	static char *g_texture_files[] = {
		"textures/gray_brick_wall_south.xpm",
		"textures/gray_brick_wall_south_shadowed.xpm",
		"textures/gray_brick_wall_east.xpm",
		"textures/gray_brick_wall_east_shadowed.xpm",
		"textures/hitler_picture.xpm",
		"textures/hitler_picture_shadowed.xpm",
		"textures/nazi_eagle_picture.xpm",
		"textures/nazi_eagle_picture_shadowed.xpm",

		"textures/ceiling_angles6.xpm",
		"textures/floor_chessed.xpm",

		"textures/office_beige_wall_flag_nazi.xpm",
		"textures/office_beige_wall_portrait_hitler.xpm",
		"textures/office_beige_wall_flag_nazi_military.xpm",
		"textures/office_beige_wall_plain.xpm",
		"textures/office_beige_archway.xpm",
		"textures/office_beige_wall_lamp.xpm",
		"textures/office_beige_window_large_curtain.xpm",
		"textures/office_beige_wall_portrait_lenin.xpm",
		"textures/office_beige_wall_portrait_stalin.xpm",

		"textures/lab_metal_grey_tiles.xpm",
		"textures/lab_metal_grey_tiles_blood1.xpm",
		"textures/lab_metal_grey_tiles_blood2.xpm",
		"textures/lab_metal_grey_tiles_blood3.xpm",
		"textures/lab_metal_grey_tiles_blood4.xpm",
		"textures/lab_metal_grey_tiles_clock.xpm",
		"textures/lab_metal_sign_radiation.xpm",
		"textures/lab_metal_light_on.xpm",


		"textures/office_beige_wall_flag_britain.xpm",
		"textures/office_beige_wall_flag_france.xpm",
		"textures/office_beige_wall_flag_japan.xpm",
		"textures/office_beige_wall_flag_soviet.xpm",
		"textures/office_beige_wall_map.xpm"
	};

	size_t	i;
	i = 0;
	g->textures = ft_calloc(TEXTR_NUMBER, sizeof (t_image *));
	while (i < TEXTR_NUMBER)
	{
		g->textures[i] = im_load_from_xpmfile(g->mlx, g_texture_files[i]);
		if (!g->textures[i])
		{
			printf("The texture %s was not loaded\n", g_texture_files[i]);
			while (--i)
				im_cleanup(g->mlx, g->textures[i]);
			game_cleanup(g);
			exit(1);
		}
		++i;
	}
}

#pragma endregion

static void	load_animations(t_game *g)
{
	static char	*animation_files[] = {
		"textures/lab_metal_white_door_sprite.xpm",
		"textures/lab_metal_grey_tiles_hexdoor_animation.xpm"
	};
	size_t		i;

	i = 0;
	g->animations = ft_calloc(ANIM_NUMBER, sizeof (t_animation *));
	while (i < ANIM_NUMBER)
	{
		g->animations[i] = im_load_from_xpmfile(g->mlx, animation_files[i]);
		if (!g->animations[i])
		{
			ft_printf("Sprite with number %d can't be loaded\n", i);
			exit(1);
		}
		++i;
	}
}

static void	init_lights(t_game *g)
{
	t_light	tmp;
	size_t	i;
	size_t	j;

	g->lights = array_init(sizeof (t_light));
	j = 0;
	while (g->map.tiles[j])
	{
		i = 0;
		while (g->map.tiles[j][i])
		{
			if (g->map.tiles[j][i] == ':')
			{
				tmp = (t_light){.pos={i + 0.5,j+0.5},.intensity = 10.f, .strength = 1.f, .color=colorf_from_uint(COLOR_GOLD)};
				array_push(&g->lights, &tmp);
			}
			else if (g->map.tiles[j][i] == 'B')
			{
				tmp = (t_light){.pos={i + 0.5,j+0.5},.intensity = 4.f, .strength = 1.f, .color=colorf_from_uint(COLOR_RED)};
				array_push(&g->lights, &tmp);
			}
			++i;
		}
		++j;
	}
}

static void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_game(ERROR_MLX_INIT, g);
	g->win = mlx_new_window(g->mlx, g->w, g->h, "cub3D");
	if (!g->win)
		exit_game(ERROR_MLX_WIN, g);

	g->buffer_image = im_get_empty(g->mlx, g->w, g->h);
	load_textures(g); // ! NOT CORRECT TEXTURE LOADING
	load_animations(g);
	init_entities(g);
	init_lights(g);
	mlx_loop_hook(g->mlx, main_loop, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, key_press_hook, g);
	mlx_key_hook(g->win, key_release_hook, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, close_window_hook, g->mlx);
	mlx_hook(g->win, MotionNotify, PointerMotionMask, mouse_move_hook, g);
	mlx_mouse_hide(g->mlx, g->win);
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
	g->rays = ft_calloc(g->w, sizeof (t_dda_ray));
	init_cubes(g->cubes);
	g->sprites = init_sprites(g);
	
	
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
