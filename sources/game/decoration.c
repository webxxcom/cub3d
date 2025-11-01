/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:12:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 22:12:01 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	door_update(t_game *const g, t_decoration *d)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
		= d->animation->frames[d->animation->curr_frame_n];
	int32_t const	frame_time = curr_frame->time;
	int32_t			step;

	(void)g;
	if (d->state == OPEN || d->state == CLOSED)
		return ;
	if (d->state == CLOSING)
		step = -1;
	else
		step = 1;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		d->animation->curr_frame_n += step;
		d->animation->frames[d->animation->curr_frame_n]->time = curr_time;
		if (d->animation->curr_frame_n + 1 == d->animation->total_frames)
			d->state = OPEN;
		else if (d->animation->curr_frame_n == 0)
			d->state = CLOSED;
	}
	d->texture = animation_get_current_image(d->animation);
}

void	door_interact(t_game *const g, t_decoration *door)
{
	(void)g;
	if (door->state == OPEN || door->state == OPENING)
		door->state = CLOSING;
	else if (door->state == CLOSING || door->state == CLOSED)
		door->state = OPENING;
}

void	anim_def_update(t_game *const g, t_decoration *self)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
		= self->animation->frames[self->animation->curr_frame_n];
	int const		frame_time = curr_frame->time;

	(void)g;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		self->animation->curr_frame_n = (self->animation->curr_frame_n + 1)
			% self->animation->total_frames;
		self->animation->frames[self->animation->curr_frame_n]
			->time = curr_time;
	}
	self->texture = animation_get_current_image(self->animation);
}

void	sprite_update_anim(t_game *const g, t_sprite *self)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame *const	curr_frame
		= self->animation->frames[self->animation->curr_frame_n];
	int const		frame_time = curr_frame->time;

	(void)g;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		self->animation->curr_frame_n = (self->animation->curr_frame_n + 1)
			% self->animation->total_frames;
		self->animation->frames[self->animation->curr_frame_n]
			->time = curr_time;
	}
	self->texture = animation_get_current_image(self->animation);
}

void	light_interact(t_game *const g, t_decoration *light)
{
	(void)g;
	(void)light;
}
