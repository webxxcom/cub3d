/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:45:50 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 12:28:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	key_handle(t_game *const game, int key)
{
	if (key == KEY_ESC)
		mlx_loop_end(game->mlx);
}

void	keyboard_handle(t_game *const game)
{
	t_list	*curr;

	curr = game->pressed_keys;
	while (curr)
	{
		key_handle(game, *((int *)curr->content));
		curr = curr->next;
	}
	handle_movement(game);
}
