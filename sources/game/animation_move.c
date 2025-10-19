/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:48:47 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 21:43:37 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	animation_update(t_game *g, t_animation *anim, int anim_state)
{
	uint64_t const	curr_time = get_time_in_ms();
	t_frame	*const	curr_frame = anim->frames[anim->curr_frame_n];
	int const		frame_time = curr_frame->time;

	(void)g;
	int	step = 1;
	if (anim_state == 2 || anim_state == 3)
		step = -1;
	if (curr_time - frame_time > ANIMATION_DELAY)
	{
		if ((anim_state == 0 && anim->curr_frame_n != 0) || (anim_state == 1 && anim->curr_frame_n + 1 != anim->total_frames))
		{
			anim->curr_frame_n = (anim->curr_frame_n + step) % anim->total_frames;
			anim->frames[anim->curr_frame_n]->time = curr_time;
		}
	}
	return (1);
}

t_image	*animation_get_current_image(t_animation *anim)
{
	return (anim->frames[anim->curr_frame_n]->image);
}
