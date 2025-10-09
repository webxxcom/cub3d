/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:16:14 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 23:30:26 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cam_rotate(t_game *const game, const float dr)
{
	const t_vec2f	dir_vec = game->cam.dir;
	const t_vec2f	plane_vec = game->cam.plane;
	const double	rot = dr * game->cam.sensitivity;

	game->cam.dir.x = dir_vec.x * cos(rot)+ dir_vec.y * sin(rot);
	game->cam.dir.y = dir_vec.x * -sin(rot) + dir_vec.y * cos(rot);
	game->cam.plane.x = plane_vec.x * cos(rot) + plane_vec.y * sin(rot);
	game->cam.plane.y = plane_vec.x * -sin(rot) + plane_vec.y * cos(rot);
}

int	mouse_move(int x, int y, t_game *game)
{
	const t_vec2i	center = vec2i_construct(game->w / 2, game->h / 2);

	(void)y;
	cam_rotate(game, (x - center.x) * game->dtime);
	mlx_mouse_move(game->mlx, game->win, center.x, center.y);
	return (1);
}

int	close_window(void *mlx)
{
	return (mlx_loop_end(mlx));
}
