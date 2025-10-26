/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 13:40:29 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static bool	load_texture(t_game *g, char *path, size_t i)
{
	g->textures[i] = im_load_from_xpmfile(g->mlx, path);
	if (!g->textures[i])
	{
		printf("The texture %s was not loaded\n", path);
		while (--i)
			im_cleanup(g->mlx, g->textures[i]);
		game_cleanup(g);
		return (false);
	}
	return (true);
}

static void	load_textures(t_game *g)
{
	size_t	i;

	i = 0;
	g->textures = ft_calloc(6, sizeof (t_image *));
	load_texture(g, g->paths.north, i++);
	load_texture(g, g->paths.west, i++);
	load_texture(g, g->paths.south, i++);
	load_texture(g, g->paths.east, i++);
	load_texture(g, g->paths.floor, i++);
	load_texture(g, g->paths.ceiling, i++);
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

static void	init_decorations(t_game *g)
{
	size_t			i;
	t_decoration	*tmp;

	i = 0;
	while (i < array_size(&g->decorations))
	{
		tmp = array_get(&g->decorations, i);
		tmp->texture = im_load_from_xpmfile(g->mlx, remove_nl(tmp->texture_path));
		if (!tmp->texture)
		{
			printf("Texture was not loaded %s\n", tmp->texture_path);
			exit(1);
		}
		++i;
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
	init_decorations(g);
	mlx_loop_hook(g->mlx, main_loop, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, key_press_hook, g);
	mlx_key_hook(g->win, key_release_hook, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, close_window_hook, g->mlx);
	mlx_hook(g->win, MotionNotify, PointerMotionMask, mouse_move_hook, g);
	mlx_mouse_hide(g->mlx, g->win);
}

static void	init_game(t_game *g, const char *filename)
{
	g->w = WINDOW_WIDTH;
	g->h = WINDOW_HEIGHT;
	g->show_dbg = false;
	g->show_keys = false;
	g->dtime = 0;
	g->last_time = get_time_in_ms();
	g->cam = cam_init();
	g->input = init_input();
	g->rays = ft_calloc(g->w, sizeof (t_dda_ray));
	g->sprites = init_sprites(g);
	g->decorations = array_init(sizeof (t_decoration));
	
	
	// ! Hard code REVISE
	g->player = player_init();
	parse(g, filename);
	g->minimap = minimap_init(g);
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
	ft_memset(game, 0, sizeof (t_game));
	init_game(game, filename);
	init_mlx(game);
	load_textures(game);
	mlx_loop(game->mlx);
	game_cleanup(game);
}
