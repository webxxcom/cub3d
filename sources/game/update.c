/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:19:02 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 17:21:52 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	update_vals(t_game *const g)
{
	if (g->state == GAME_STATE_ON)
	{
		g->player.dir = g->cam.dir;
		g->player.plane = g->cam.plane;
	}
}

static inline void	update_cutscenes(t_game *g)
{
	t_cutscene	*cs;
	size_t		i;

	i = 0;
	while (i < array_size(&g->cutscenes))
	{
		cs = array_get(&g->cutscenes, i);
		if (cs && cs->is_going)
			cutscene_update(g, cs);
		++i;
	}
}

inline void	update(t_game *g)
{
	update_vals(g);
	process_dtime(g);
	update_animations(g);
	update_cutscenes(g);
	repetition_handle(g);
}
