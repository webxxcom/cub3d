/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:44:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/12 09:46:17 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	int_eq(void *a, void *b)
{
	return (*((int *)a) - *((int *)b));
}

int	key_release_hook(int key, t_game *game)
{
	if (movement_key(key))
		process_mvkeys(game, key, false);
	else
	{
		if (key_should_repeat(key))
			ft_lst_remove_if(&game->input.pressed_keys, &key, int_eq, free);
		else
			process_keypress(game, key);
	}
	return (1);
}
