/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:44:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/30 19:00:51 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	remove_repeating_key(t_game *g, int key)
{
	int		*tmp;
	size_t	i;

	i = 0;
	while (i < array_size(&g->input.pressed_keys))
	{
		tmp = array_get(&g->input.pressed_keys, i);
		if (*tmp == key)
		{
			array_remove(&g->input.pressed_keys, i);
			return ;
		}
		++i;
	}
}

int	key_release_hook(int key, t_game *game)
{
	if (game->state != GAME_STATE_ON)
		return (1);
	if (movement_key(key))
		process_mvkeys(game, key, false);
	else
	{
		if (key_should_repeat(key))
			remove_repeating_key(game, key);
		else
			process_keypress(game, key);
	}
	return (1);
}
