/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/15 22:34:43 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_all_animations(t_game *const g)
{
	size_t	i;

	i = 0;
	while (i < ANIM_NUMBER)
		animate(g, g->animations[i++], 0);
}

int	main_loop(t_game *g)
{
	g->player.speed = g->player.base_speed;
	process_dtime(g);
	update_all_animations(g);
	repetition_handle(g);
	game_render(g);
	return (1);
}
