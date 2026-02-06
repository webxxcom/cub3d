/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:45:50 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/06 15:04:42 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	repetition_handle(t_game *const g)
{
	int		*tmp;
	size_t	i;

	if (g->state != GAME_STATE_ON)
		return ;
	i = 0;
	while (i < array_size(&g->input.pressed_keys))
	{
		tmp = array_get(&g->input.pressed_keys, i);
		if (tmp)
			process_keypress(g, *tmp);
		++i;
	}
	handle_movement(g);
}

static void	process_repetition_key(t_game *g, int k)
{
	array_push(&g->input.pressed_keys, &k);
}

int	key_press_hook(int key, t_game *game)
{
	if (game->state != GAME_STATE_ON)
		return (1);
	if (movement_key(key))
		process_mvkeys(game, key, true);
	else if (key_should_repeat(key))
		process_repetition_key(game, key);
	return (1);
}
