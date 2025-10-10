/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:39:06 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 19:02:55 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline bool	movement_key(int key)
{
	return (key == KEY_W || key == KEY_A
		|| key == KEY_S || key == KEY_D);
}

inline bool key_should_repeat(int key)
{
    return (key != KEY_F1);
}

void	process_mvkeys(t_game *const g, int key, bool pressed)
{
	if (key == KEY_W)
		g->moving_keys[MOVING_FRWD] = pressed;
	if (key == KEY_S)
		g->moving_keys[MOVING_BCK] = pressed;
	if (key == KEY_A)
		g->moving_keys[MOVING_LFT] = pressed;
	if (key == KEY_D)
		g->moving_keys[MOVING_RGHT] = pressed;
}

void	process_keypress(t_game *const game, int key)
{
	if (key == KEY_F1)
		toggle_bool(&game->show_dbg);
	else if (key == KEY_ESC)
		mlx_loop_end(game->mlx);
}
