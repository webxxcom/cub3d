/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:06:44 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/16 00:06:03 by webxxcom         ###   ########.fr       */
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

void	draw_line(t_image *im, t_vec2i start, t_vec2i end, uint32_t col)
{
	t_vec2i	delta;
	t_vec2i	step;
	int		err;

	delta = vec2i_construct(abs(end.x - start.x), abs(end.y - start.y));
	step = get_step_for_line(start, end);
	err = delta.x - delta.y;
	while (1)
	{
		im_set_pixel(im, start.x, start.y, col);
		if (start.x == end.x  && start.y == end.y)
			break;
		process_step_condition(&err, &start, step, delta);
	}
}

static void	fill_circle_oct(t_image *im, t_vec2i c, t_vec2i p, int32_t col)
{
	draw_line(im, vec2i_construct(c.x - p.x, c.y + p.y),
		vec2i_construct(c.x + p.x, c.y + p.y), col);
	draw_line(im, vec2i_construct(c.x - p.x, c.y - p.y),
		vec2i_construct(c.x + p.x, c.y - p.y), col);
	draw_line(im, vec2i_construct(c.x - p.y, c.y + p.x),
		vec2i_construct(c.x + p.y, c.y + p.x), col);
	draw_line(im, vec2i_construct(c.x - p.y, c.y - p.x),
		vec2i_construct(c.x + p.y, c.y - p.x), col);
}

void	draw_circle(t_image *im, t_vec2i c, int32_t r, uint32_t col)
{
	float	p;
	int32_t	x;
	int32_t	y;

	x = 0;
	y = -r;
	p = -r;
	while(x < -y)
	{
		if (p > 0)
		{
			p += 2 * (y) + 1;
			++y;
		}
		else
			p += 2 * x + 1;
		fill_circle_oct(im, c, vec2i_construct(x, y), col);
		++x;
	}
}
