/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:12:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 23:37:20 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	door_update(t_game *const g, t_entity *door)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
		= door->anim->frames[door->anim->curr_frame_n];
	int const		frame_time = curr_frame->time;
	int				step;

	if (door->state == OPEN || door->state == CLOSED)
		return ;
	if (door->state == CLOSING || door->state == CLOSED)
		step = -1;
	else
		step = 1;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		door->anim->curr_frame_n = door->anim->curr_frame_n + step;
		door->anim->frames[door->anim->curr_frame_n]->time = curr_time;
		if (door->anim->curr_frame_n == door->anim->total_frames - 1)
		{
			door->state = OPEN;
			g->map.tiles[door->pos.y][door->pos.x] = 'O';
		}
		else if (door->anim->curr_frame_n == 0)
			door->state = CLOSED;
	}
}

void	door_interact(t_game *const g, t_entity *door)
{
	if (door->state == OPEN || door->state == OPENING)
	{
		door->state = CLOSING;
		g->map.tiles[door->pos.y][door->pos.x] = 'D';
	}
	else if (door->state == CLOSING || door->state == CLOSED)
	{
		door->state = OPENING;
	}
}
