/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:45:50 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 23:35:17 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_walkable(t_game *g, float x, float y)
{
	return (g->map[(int)y][(int)x] == '0');
}

static t_vec2i	get_signs(t_vec2f dir_vec)
{
	int	x;
	int	y;

	if (dir_vec.x < 0)
		x = -1;
	else
		x = 1;
	if (dir_vec.y < 0)
		y = -1;
	else
		y = 1;
	return (vec2i_construct(x, y));
}

static void	move(t_game *const game, t_vec2f dir_vec)
{
	t_player *const	pl = &game->player;
	const t_vec2f	delta = vec2f_construct(
			dir_vec.x * pl->speed * game->dtime,
			dir_vec.y * pl->speed * game->dtime);
	const t_vec2f	new_pos = vec2f_translate(pl->pos, delta.x, delta.y);
	const t_vec2i	sign = get_signs(dir_vec);

	if (is_walkable(game, new_pos.x + pl->radius * sign.x, pl->pos.y))
		pl->pos.x = new_pos.x;
	if (is_walkable(game, pl->pos.x, new_pos.y + pl->radius * sign.y))
		pl->pos.y = new_pos.y;
}

static void	key_handle(t_game *const game, int key)
{
	const t_vec2f	plane_norm = game->cam.plane;
	t_vec2f			mv_dir;

	mv_dir = vec2f_init();
	if (key == KEY_W)
		mv_dir = vec2f_translate(mv_dir, game->cam.dir.x, game->cam.dir.y);
	if (key == KEY_S)
		mv_dir = vec2f_translate(mv_dir, -game->cam.dir.x, -game->cam.dir.y);
	if (key == KEY_D)
		mv_dir = vec2f_translate(mv_dir, plane_norm.x, plane_norm.y);
	if (key == KEY_A)
		mv_dir = vec2f_translate(mv_dir, -plane_norm.x, -plane_norm.y);
	if (mv_dir.x != 0 || mv_dir.y != 0)
		move(game, vec2f_normalize(mv_dir));
	if (key == KEY_ESC)
		mlx_loop_end(game->mlx);
}

void	keyboard_handle(t_game *const game)
{
	t_list	*curr;

	curr = game->pressedKeys;
	while (curr)
	{
		key_handle(game, *((int *)curr->content));
		curr = curr->next;
	}
}
