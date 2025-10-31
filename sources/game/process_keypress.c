/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:39:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/31 12:23:39 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline bool	movement_key(int key)
{
	return (key == KEY_W || key == KEY_A
		|| key == KEY_S || key == KEY_D
		|| key == KEY_UP || key == KEY_LEFT
		|| key == KEY_RIGHT || key == KEY_DOWN);
}

inline bool	key_should_repeat(int key)
{
	return (key != KEY_F1 && key != KEY_F2 && key != KEY_F);
}

void	process_mvkeys(t_game *const g, int key, bool pressed)
{
	if (key == KEY_W || key == KEY_UP)
		g->input.moving_keys[MOVING_FRWD] = pressed;
	if (key == KEY_S || key == KEY_DOWN)
		g->input.moving_keys[MOVING_BCK] = pressed;
	if (key == KEY_A || key == KEY_LEFT)
		g->input.moving_keys[MOVING_LFT] = pressed;
	if (key == KEY_D || key == KEY_RIGHT)
		g->input.moving_keys[MOVING_RGHT] = pressed;
}

static void	player_interact(t_game *const g)
{
	t_vec2i const	dir = vec2i_construct(
			g->player.pos.x + g->cam.dir.x, g->player.pos.y + g->cam.dir.y);
	t_decoration	*decor;

	decor = find_decoration_at(g, dir);
	if (decor && decor->interact)
		decor->interact(g, decor);
}

void	process_keypress(t_game *const g, int key)
{
	if (key == KEY_F1)
		toggle_bool(&g->show_dbg);
	if (key == KEY_F2)
		toggle_bool(&g->show_keys);
	if (key == KEY_LSHIFT)
		g->player.speed = g->player.sprint_speed;
	if (key == KEY_F)
		player_interact(g);
	else if (key == KEY_ESC)
		mlx_loop_end(g->mlx);
}
