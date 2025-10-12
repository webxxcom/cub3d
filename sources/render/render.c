/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/12 11:37:41 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"

#pragma region DEBUG
// ! Debug function is not complient with shitty
//		norminette so need to comment it for release
static void	render_debug(t_game *g)
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

		// Pressed keys
		snprintf(buf, sizeof(buf), "Keys: W:%d A:%d S:%d D:%d",
			g->input.moving_keys[0], g->input.moving_keys[1],
			g->input.moving_keys[2], g->input.moving_keys[3]);

		// Textures loaded check
		int loaded = 1;
		for (int c = 0; c < 2; c++)
			for (int w = 0; w < 4; w++)
				if (!g->cubes[c].walls[w])
					loaded = 0;

		snprintf(buf, sizeof(buf), "Textures: %s", loaded ? "ALL LOADED" : "MISSING");
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
	}
}

#pragma endregion

void	draw_keybindings(t_game *g)
{
	const int	DBG_X = 10;
	const int	DBG_Y = g->h / 3;
	const int	DBG_LINE_H = 20;
	int			y;

	if (!g->show_keys)
		return;
	y = DBG_Y;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "W / ARROW_UP : Move forward");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "S / ARROW_DOWN : Move backward");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "A / ARROW_LEFT : Move left");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "D / ARROW_RIGHT : Move right");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "Left Shift : Sprint");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "F1 : Toggle debug info");
	y += DBG_LINE_H;
	mlx_string_put(g->mlx, g->win, DBG_X, y, 0xFFFFFF, "ESC : Quit");
}

static void	drawVertLine(t_game *const g, int screen_x, int line_h, float dist, t_txtres_sides side, t_vec2f ray_dir)
{
	int	y_start;
	int	y_end;
	int	y;
	
	y_start = (g->h / 2) - (line_h / 2) + g->cam.pitch;
	if (y_start < 0)
		y_start = 0;
	y_end = (g->h / 2) + (line_h / 2) + g->cam.pitch;
	if (y_end >= g->h)
		y_end = g->h - 1;

	y = y_start;

	double wallX;
	if (side == EAST || side == WEST)
		wallX = g->player.pos.y + dist * ray_dir.y;
	else
		wallX = g->player.pos.x + dist * ray_dir.x;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)g->cubes[0].walls[side]->width);
	if(side == WEST) texX = g->cubes[0].walls[side]->width - texX - 1;
    if(side == SOUTH) texX = g->cubes[0].walls[side]->width - texX - 1;
	double step = 1.0 * g->cubes[0].walls[side]->height / line_h;
	double texPos = (y_start - g->cam.pitch - g->h / 2.0 + line_h / 2.) * step;
	while (y < y_end)
	{
		int texY = (int)texPos % g->cubes[0].walls[side]->height;
        uint32_t color = im_get_pixel(g->cubes[0].walls[side], texX, texY);
		texPos += step;
		im_set_pixel(g->buffer_image, screen_x, y, color);
		y++;
	}
}

static void put_map(t_game *const g)
{
	int		screen_x;
	t_dda_res	dda_res;

	screen_x = 0;
	while (screen_x < g->w)
	{
		dda_res = perform_dda(g, screen_x);
		drawVertLine(g, screen_x, g->h / dda_res.dist, dda_res.dist, dda_res.side, dda_res.ray_dir);
		++screen_x;
	}
}

static void	put_buffer(t_game *const game)
{
	im_clear(game->buffer_image);
	put_map(game);
	put_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer_image->image, 0, 0);
}

void	game_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	put_buffer(game);
	render_debug(game);
	draw_keybindings(game);
}