/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:16:14 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/13 21:44:25 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cam_rotate(t_game *const g, const float dx, float const dy)
{
	const t_vec2f	dir_vec = g->cam.dir;
	const t_vec2f	plane_vec = g->cam.plane;
	const double	rot = -dx * g->cam.sensitivity;

	g->cam.dir.x = dir_vec.x * cos(rot) - dir_vec.y * sin(rot);
	g->cam.dir.y = dir_vec.x * sin(rot) + dir_vec.y * cos(rot);
	g->cam.plane.x = plane_vec.x * cos(rot) - plane_vec.y * sin(rot);
	g->cam.plane.y = plane_vec.x * sin(rot) + plane_vec.y * cos(rot);
	if ((dy < 0 && g->cam.pitch < g->h * 2)
		|| (dy > 0 && - g->cam.pitch < g->h * 2))
		g->cam.pitch -= dy * g->cam.sensitivity * g->h;
}

int	mouse_move_hook(int x, int y, t_game *g)
{
	const t_vec2i	center = vec2i_construct(g->w / 2, g->h / 2);

	cam_rotate(g, x - center.x, y - center.y);
	mlx_mouse_move(g->mlx, g->win, center.x, center.y);
	return (1);
}

int	close_window_hook(void *mlx)
{
	return (mlx_loop_end(mlx));
}
