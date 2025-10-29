/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/29 10:20:41 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	update_animations(t_game *g)
{
	t_decoration	*tmp;
	size_t			i;

	i = 0;
	while (i < array_size(&g->map.decorations))
	{
		tmp = array_get(&g->map.decorations, i);
		if (!tmp)
			continue ;
		if (tmp->update)
			tmp->update(g, tmp);
		++i;
	}
}

int	main_loop(t_game *g)
{
	g->player.speed = g->player.base_speed;
	process_dtime(g);
	update_animations(g);
	repetition_handle(g);
	game_render(g);
	return (1);
}
