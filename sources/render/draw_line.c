/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:06:44 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 16:51:11 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline t_vec2i	get_step_for_line(t_vec2i const start, t_vec2i const end)
{
	t_vec2i	step;
	
	step = vec2i_init();
	if (start.x < end.x)
		step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	return (step);
}

static inline void	process_step_condition(int *err, t_vec2i *start, t_vec2i step, t_vec2i delta)
{
	const int	e2 = 2 * *err;

	if (e2 > -delta.y)
	{
		*err = *err - delta.y;
		start->x += step.x;
	}
	if (e2 < delta.x)
	{
		*err = *err + delta.x;
		start->y += step.y;
	}
}

void	draw_line(t_game *g, t_vec2f start_f, t_vec2f end_f, uint32_t col)
{
	t_vec2i	starti;
	t_vec2i	endi;
	t_vec2i	delta;
	t_vec2i	step;
	int		err;

	starti = vec2i_construct(round(start_f.x), round(start_f.y));
	endi = vec2i_construct(round(end_f.x), round(end_f.y));
	delta = vec2i_construct(abs(endi.x - starti.x), abs(endi.y - starti.y));
	step = get_step_for_line(starti, endi);
	err = delta.x - delta.y;
	while (1)
	{
		im_set_pixel(g->buffer_image, starti.x, starti.y, im_scale_pixel(col, 1. / starti.x));
		if (starti.x == endi.x  && starti.y == endi.y)
			break;
		process_step_condition(&err, &starti, step, delta);
	}
}