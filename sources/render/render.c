/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:59 by phutran           #+#    #+#             */
/*   Updated: 2026/02/06 16:01:56 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// ! Debug function is not complient with shitty
//		norminette so need to comment it for release
#pragma region DEBUG
static void	render_debug_info(t_game *g)
{
	if (g->show_dbg)
	{
		char	buf[256];
		int		y = 10;

		// Player pos
		snprintf(buf, sizeof(buf), "Player Pos: x=%.2f y=%.2f",
			g->player.pos.x, g->player.pos.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Player Direction
		snprintf(buf, sizeof(buf), "Player Dir: x=%.2f y=%.2f",
			g->player.dir.x, g->player.dir.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Player Plane
		snprintf(buf, sizeof(buf), "Player Plane: x=%.2f y=%.2f",
			g->player.plane.x, g->player.plane.y);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Player speed and radius
		snprintf(buf, sizeof(buf), "Speed: %.2f Radius: %.2f",
			g->player.speed, g->player.radius);
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
		y += 15;

		// Camera pos
		snprintf(buf, sizeof(buf), "Cam Pos: x=%.2f y=%.2f",
			g->cam.pos.x, g->cam.pos.y);
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
		mlx_string_put(g->mlx, g->win, 10, y, 0xFFFFFF, buf);
	}
}

#pragma endregion

static void	put_lines(t_game *const g)
{
	int32_t	screen_x;

	draw_floor_and_ceiling(g);
	screen_x = 0;
	while (screen_x < g->w)
	{
		g->rays[screen_x] = perform_dda(g, screen_x);
		draw_vert_line(g, screen_x, g->rays[screen_x]);
		g->z_buffer[screen_x] = g->rays[screen_x].crossed_textures[0].dist;
		++screen_x;
	}
}

static bool	decor_direction_matches(t_game *g, t_decoration *d)
{
	t_vec2f const	dir = g->player.dir;

	return (d->type == DECOR_DOOR
		|| (d->direction == NORTH && dir.y > 0)
		|| (d->direction == SOUTH && dir.y < 0)
		|| (d->direction == WEST && dir.x < 0)
		|| (d->direction == EAST && dir.x > 0));
}

static void	put_interact_text(t_game *g)
{
	t_vec2f const	dir = vec2f_construct(
			g->player.pos.x + g->cam.dir.x, g->player.pos.y + g->cam.dir.y);
	t_decoration	*decor;
	t_sprite		*sprite;

	decor = find_decoration_at(g, vec2i_construct(dir.x, dir.y));
	if (decor && decor_direction_matches(g, decor))
	{
		if (decor->interact)
			put_ui_text(g, decor->interact_text, COLOR_WHITE);
		else
			put_ui_text(g, decor->looking_at_text, COLOR_WHITE);
	}
	sprite = find_sprite_at(g, dir);
	if (sprite)
	{
		if (sprite->interact)
			put_ui_text(g, sprite->interact_text, COLOR_WHITE);
		else
			put_ui_text(g, sprite->looking_at_text, COLOR_WHITE);
	}
}

static void	put_buffer(t_game *const g)
{
	im_clear(g->buffer_image);
	put_lines(g);
	put_sprites(g);
	put_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win,
		g->buffer_image->image, 0, 0);
	put_interact_text(g);
}

void	game_render(t_game *g)
{
	put_buffer(g);
	draw_keybindings(g);
	render_debug_info(g);
}
