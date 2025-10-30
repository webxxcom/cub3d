/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:45:08 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 22:57:19 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

static void	load_texture(t_game *g, char *path, size_t i)
{
	g->textures[i] = im_load_from_xpmfile(g->mlx, path);
	if (!g->textures[i])
		exit_game("load_texture", g);
}

static void	load_textures(t_game *g)
{
	size_t const	tex_count = 6;
	size_t			i;

	i = 0;
	g->textures = ft_calloc(tex_count + 1, sizeof (t_image *));
	if (!g->textures)
		exit_game("load_textures", g);
	load_texture(g, g->paths.north, i++);
	load_texture(g, g->paths.west, i++);
	load_texture(g, g->paths.south, i++);
	load_texture(g, g->paths.east, i++);
	load_texture(g, g->paths.floor, i++);
	load_texture(g, g->paths.ceiling, i++);
	freenull(&g->paths.north);
	freenull(&g->paths.west);
	freenull(&g->paths.south);
	freenull(&g->paths.east);
	freenull(&g->paths.floor);
	freenull(&g->paths.ceiling);
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
	load_textures(g);
	load_decorations(g);
	mlx_loop_hook(g->mlx, main_loop, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, key_press_hook, g);
	mlx_key_hook(g->win, key_release_hook, g);
	mlx_hook(g->win, DestroyNotify, NoEventMask, close_window_hook, g->mlx);
	mlx_hook(g->win, MotionNotify, PointerMotionMask, mouse_move_hook, g);
	mlx_mouse_hide(g->mlx, g->win);
}

t_cutscene init_start_cutscene(t_game *g)
{
	t_cutscene	res;

	ft_memset(&res, 0, sizeof (t_cutscene));
	res.speed = 0.1f;
	res.dtime = get_time_in_ms();
	res.is_going = true;
	res.curve.p0 = vec2f_construct(g->player.pos.x - 0.8f, g->player.pos.y - 9.f);
    res.curve.p1 = vec2f_construct(g->player.pos.x + 2.f, g->player.pos.y - 2.f);
    res.curve.p2 = g->player.pos;
	g->show_dbg = true;
	return (res);
}

static void	init_cutscenes(t_game *g)
{
	t_cutscene tmp;

	g->cutscenes = array_init(sizeof (t_cutscene));
	tmp = init_start_cutscene(g);
	array_push(&g->cutscenes, &tmp);
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
	g->player = player_init();
	g->map.decorations = array_init(sizeof (t_decoration));
	parse(g, filename);
	g->minimap = minimap_init(g);
	g->state = GAME_STATE_CUTSCENE;
	init_cutscenes(g);
}

void	start_game(t_game *game, const char *filename)
{
	ft_memset(game, 0, sizeof (t_game));
	init_game(game, filename);
	init_mlx(game);
	mlx_loop(game->mlx);
	game_cleanup(game);
}
