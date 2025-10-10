/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:44:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 12:28:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	process_mvkeys(t_game *const g, int key, bool val)
{
	if (key == KEY_W)
		g->moving_keys[MOVING_FRWD] = val;
	if (key == KEY_S)
		g->moving_keys[MOVING_BCK] = val;
	if (key == KEY_A)
		g->moving_keys[MOVING_LFT] = val;
	if (key == KEY_D)
		g->moving_keys[MOVING_RGHT] = val;
}

static bool	movement_key(int key)
{
	return (key == KEY_W || key == KEY_A
		|| key == KEY_S || key == KEY_D);
}

int	key_press(int key, t_game *game)
{
	int	*key_p;

	if (movement_key(key))
		process_mvkeys(game, key, true);
	else
	{
		key_p = malloc(sizeof (int));
		*key_p = key;
		ft_lstadd_front(&game->pressed_keys, ft_lstnew(key_p));
	}
	return (1);
}

static int	int_eq(void *a, void *b)
{
	return (*((int *)a) - *((int *)b));
}

int	key_release(int key, t_game *game)
{
	if (movement_key(key))
		process_mvkeys(game, key, false);
	else
		ft_lst_remove_if(&game->pressed_keys, &key, int_eq, free);
	return (1);
}
