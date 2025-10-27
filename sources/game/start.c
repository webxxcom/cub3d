/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/27 17:41:54 by webxxcom         ###   ########.fr       */
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

// static void	init_lights(t_game *g)
// {
// 	t_light	tmp;
// 	size_t	i;
// 	size_t	j;

// 	g->lights = array_init(sizeof (t_light));
// 	j = 0;
// 	while (j < g->map.size.y)
// 	{
// 		i = 0;
// 		while (i < g->map.size.x)
// 		{
// 			if (g->map.tiles[j][i].type == ':')
// 			{
// 				tmp = (t_light){.pos={i + 0.5,j+0.5},.intensity = 10.f, .strength = 1.f, .color=colorf_from_uint(COLOR_GOLD)};
// 				array_push(&g->lights, &tmp);
// 			}
// 			else if (g->map.tiles[j][i] == 'B')
// 			{
// 				tmp = (t_light){.pos={i + 0.5,j+0.5},.intensity = 4.f, .strength = 1.f, .color=colorf_from_uint(COLOR_RED)};
// 				array_push(&g->lights, &tmp);
// 			}
// 			++i;
// 		}
// 		++j;
// 	}
// }

void load_decorations(t_game *g)
{
	t_tile			*tile;
	t_decoration	*tmp;
	t_vec2i			pos;
	size_t			i;

	i = 0;
	while (i < array_size(&g->map.decorations))
	{
		tmp = array_get(&g->map.decorations, i);
		pos = tmp->pos;
		tile = &g->map.tiles[pos.y][pos.x];
		if (tmp->type == DECOR_DOOR)
		{
			tile->type = TILE_DOOR;
			tile->sides[0] = tmp;
			tile->sides[1] = tmp;
			tile->sides[2] = tmp;
			tile->sides[3] = tmp;
			tmp->animation = init_animation(g, tmp->texture_path);
			if (!tmp->animation)
			{
				printf("Texture was not loaded %s\n", tmp->texture_path);
				exit(1);
			}
			tmp->texture = animation_get_current_image(tmp->animation); // ! REVISE
			tmp->update = door_update;
			tmp->interact = door_interact;
		}
		else
		{
			tile->sides[tmp->direction] = tmp;
			tile->type = TILE_WALL;
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
	load_decorations(g);
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
	//g->sprites = init_sprites(g);
	
	
	// ! Hard code REVISE
	g->player = player_init();
	g->map.decorations = array_init(sizeof (t_decoration));
	parse(g, filename);
	g->minimap = minimap_init(g);
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
