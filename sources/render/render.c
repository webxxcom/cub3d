/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/15 22:49:45 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

#pragma region DEBUG
// ! Debug function is not complient with shitty
//		norminette so need to comment it for release
static void	render_debug_info(t_game *g)
{
	if (g->show_dbg)
	{
		char	buf[128];
		int		y = 10;

		// Player pos
		snprintf(buf, sizeof(buf), "Player: x=%.2f y=%.2f",
			g->player.pos.x, g->player.pos.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Player speed and radius
		snprintf(buf, sizeof(buf), "Speed: %.2f Radius: %.2f",
			g->player.speed, g->player.radius);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Camera direction
		snprintf(buf, sizeof(buf), "Cam Dir: x=%.2f y=%.2f",
			g->cam.dir.x, g->cam.dir.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Camera plane
		snprintf(buf, sizeof(buf), "Cam Plane: x=%.2f y=%.2f",
			g->cam.plane.x, g->cam.plane.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Sensitivity and pitch
		snprintf(buf, sizeof(buf), "Sensitivity: %.2f Pitch: %.2f",
			g->cam.sensitivity, g->cam.pitch);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Delta time
		snprintf(buf, sizeof(buf), "dTime: %.4f", g->dtime);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// FPS
		snprintf(buf, sizeof(buf), "FPS: %.1f", 1. / g->dtime);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Pressed keys
		snprintf(buf, sizeof(buf), "Keys: W:%d A:%d S:%d D:%d",
			g->input.moving_keys[0], g->input.moving_keys[1],
			g->input.moving_keys[2], g->input.moving_keys[3]);

		// Textures loaded check
		int loaded = 1;
		for (int i = 0; i < 2; i++)
			if (!g->textures[i])
				loaded = 0;

		snprintf(buf, sizeof(buf),
			"Textures: %s", loaded ? "ALL LOADED" : "MISSING");
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
	}
}

#pragma endregion

void	draw_keybindings(t_game *g)
{
	const int	dbg_x = 10;
	const int	dbg_y = g->h / 3;
	const int	dbg_line_h = 20;
	int			y;

	if (!g->show_keys)
		return ;
	y = dbg_y;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"W / ARROW_UP : Move forward");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"S / ARROW_DOWN : Move backward");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"A / ARROW_LEFT : Move left");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"D / ARROW_RIGHT : Move right");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"Left Shift : Sprint");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"F1 : Toggle debug info");
}

static void	put_lines(t_game *const g)
{
	int			screen_x;

	draw_floor_and_ceiling(g);
	screen_x = 0;
	while (screen_x < g->w)
	{
		draw_vert_line(g, screen_x);
		++screen_x;
	}
}

static void	calculate_each_ray(t_game *g)
{
	int32_t	screen_x;

	screen_x = 0;
	while (screen_x < g->w)
	{
		g->rays[screen_x] = perform_dda(g, screen_x);
		++screen_x;
	}
}

static void	put_buffer(t_game *const game)
{
	im_clear(game->buffer_image);
	calculate_each_ray(game);
	put_lines(game);
	put_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->buffer_image->image, 0, 0);
}

void	game_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	put_buffer(game);
	render_debug_info(game);
	draw_keybindings(game);
}
