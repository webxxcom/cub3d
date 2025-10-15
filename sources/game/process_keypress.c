/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:39:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 19:15:25 by webxxcom         ###   ########.fr       */
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


static bool	is_interactable(t_game *const g, t_vec2f pos)
{
	(void)g;
	(void)pos;
	return (true);
}

static void	player_interact(t_game *const g)
{
	const t_vec2f dir = vec2f_construct(
		g->player.pos.x + g->cam.dir.x, g->player.pos.y + g->cam.dir.y);
	
	if (is_interactable(g, dir))
	{
		if (g->map.tiles[(int)dir.y][(int)dir.x] == 'D')
			g->map.tiles[(int)dir.y][(int)dir.x] = 'O';
		else if (g->map.tiles[(int)dir.y][(int)dir.x] == 'O')
			g->map.tiles[(int)dir.y][(int)dir.x] = 'D';
	}
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
