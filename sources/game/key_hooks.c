/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:44:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 13:02:15 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int key_press(int key, t_game *game)
{
	int	*vKey;

	vKey = malloc(sizeof (int));
	*vKey = key;
	ft_lstadd_front(&game->pressedKeys, ft_lstnew(vKey));
	return (1);
}

static int int_eq(void *a, void *b)
{
	return (*((int *)a) - *((int *)b));
}

int	key_release(int key, t_game *game)
{
	ft_lst_remove_if(&game->pressedKeys, &key, int_eq, free);
	return (1);
}