/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/31 14:31:04 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	main_loop(t_game *g)
{
	process_dtime(g);
	update_animations(g);
	update_cutscenes(g);
	repetition_handle(g);
	game_render(g);
	return (1);
}
