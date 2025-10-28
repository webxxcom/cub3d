/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:12:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 19:35:33 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	door_update(t_game *const g, t_decoration *door)
{
	(void)g;
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
		= door->animation->frames[door->animation->curr_frame_n];
	int const		frame_time = curr_frame->time;
	int				step;

	if (door->state == OPEN || door->state == CLOSED)
		return ;
	if (door->state == CLOSING)
		step = -1;
	else
		step = 1;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		door->animation->curr_frame_n += step;
		door->animation->frames[door->animation->curr_frame_n]->time = curr_time;
		if (door->animation->curr_frame_n + 1 == door->animation->total_frames)
			door->state = OPEN;
		else if (door->animation->curr_frame_n == 0)
			door->state = CLOSED;
	}
	door->texture = animation_get_current_image(door->animation);
}

void	door_interact(t_game *const g, t_decoration *door)
{
	(void)g;
	if (door->state == OPEN || door->state == OPENING)
		door->state = CLOSING;
	else if (door->state == CLOSING || door->state == CLOSED)
		door->state = OPENING;
}

void	light_update(t_game *const g, t_decoration *light)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
	= light->animation->frames[light->animation->curr_frame_n];
	int const		frame_time = curr_frame->time;
	(void)g;

	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		light->animation->curr_frame_n = (light->animation->curr_frame_n + 1)
			% light->animation->total_frames;
		light->animation->frames[light->animation->curr_frame_n]->time = curr_time;
	}
	light->texture = animation_get_current_image(light->animation);
}

void	light_interact(t_game *const g, t_decoration *light)
{
	(void)g;
	(void)light;
}
