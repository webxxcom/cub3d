/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 19:12:03 by webxxcom         ###   ########.fr       */
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

void update_cutscene(t_game *g, size_t idx)
{
	t_cutscene	*curr_cs = array_get(&g->cutscenes, idx);

	if (curr_cs->is_going)
	{
		if (curr_cs->curr_frame + 1 >= array_size(&curr_cs->cam_keyframes))
		{
			g->state = GAME_STATE_ON;
			curr_cs->curr_frame = 0;
			curr_cs->is_going = false;
		}
		else
		{
			t_camera_keyframe *curr_keyframe = array_get(&curr_cs->cam_keyframes, curr_cs->curr_frame);
			t_camera_keyframe *next_keyframe = array_get(&curr_cs->cam_keyframes, curr_cs->curr_frame + 1);
			const float	delta = next_keyframe->pos.y / curr_keyframe->pos.y * curr_cs->speed;
			if (curr_cs->dtime > curr_cs->speed)
			{
				g->player.pos.y += delta;
				curr_cs->dtime = get_time_in_ms();
			}
			if (g->player.pos.y > next_keyframe->pos.y)
				curr_cs->curr_frame++;
		}
	}
}

int	main_loop(t_game *g)
{
	g->player.speed = g->player.base_speed;
	process_dtime(g);
	update_animations(g);
	repetition_handle(g);
	update_cutscene(g, 0);
	game_render(g);
	return (1);
}
