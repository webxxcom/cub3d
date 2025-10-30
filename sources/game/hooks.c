/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:16:14 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/30 21:58:07 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	cam_get_plane_vec(t_vec2f dir_vec)
{
	return (vec2f_construct(-dir_vec.y * CAMERA_FOV, dir_vec.x * CAMERA_FOV));
}

void	cam_rotate(t_game *const g, const float dx, float const dy)
{
	t_vec2f const	dir_vec = g->cam.dir;
	float const		rot = -dx * g->cam.sensitivity;
	float const		sin_res = sinf(rot);
	float const		cos_res = cosf(rot);

	g->cam.dir.x = dir_vec.x * cos_res - dir_vec.y * sin_res;
	g->cam.dir.y = dir_vec.x * sin_res + dir_vec.y * cos_res;
	g->cam.plane = cam_get_plane_vec(g->cam.dir);
	if ((dy < 0 && g->cam.pitch < g->h * 2)
		|| (dy > 0 && - g->cam.pitch < g->h * 2))
		g->cam.pitch -= dy * g->cam.sensitivity * g->h;
}

int	mouse_move_hook(int x, int y, t_game *g)
{
	const t_vec2f	center = vec2f_construct(g->w / 2.f, g->h / 2.f);

	if (g->state != GAME_STATE_ON)
		return (1);
	cam_rotate(g, center.x - x, y - center.y);
	mlx_mouse_move(g->mlx, g->win, center.x, center.y);
	return (1);
}

int	close_window_hook(void *mlx)
{
	return (mlx_loop_end(mlx));
}
