/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:45:50 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/12 09:46:21 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	repetition_handle(t_game *const game)
{
	t_list	*curr;

	curr = game->input.pressed_keys;
	while (curr)
	{
		process_keypress(game, *((int *)curr->content));
		curr = curr->next;
	}
	handle_movement(game);
}

static void	process_repetition_key(t_game *g, int k)
{
	int	*key_p;

	key_p = malloc(sizeof (int));
	if (!key_p)
	{
		ft_putendl_fd("The key was not pressed because malloc failed",
			STDERR_FILENO);
		return ;
	}
	*key_p = k;
	ft_lstadd_front(&g->input.pressed_keys, ft_lstnew(key_p));
}

int	key_press_hook(int key, t_game *game)
{
	if (movement_key(key))
		process_mvkeys(game, key, true);
	else if (key_should_repeat(key))
		process_repetition_key(game, key);
	return (1);
}
