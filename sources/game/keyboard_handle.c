/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:45:50 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 13:08:16 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate(t_game *const game, const float rotation)
{
	const t_vec2f dirVec = game->cam.dir; 
	const t_vec2f planeVec = game->cam.plane;

	game->cam.dir.x = dirVec.x * cos(rotation) + dirVec.y * sin(rotation);
	game->cam.dir.y = dirVec.x * -sin(rotation) + dirVec.y * cos(rotation);

	game->cam.plane.x = planeVec.x * cos(rotation) + planeVec.y * sin(rotation);
	game->cam.plane.y = planeVec.x * -sin(rotation) + planeVec.y * cos(rotation);
}

static void	key_handle(t_game *const game, int key)
{
	t_player	*const pl = &game->player;
	
	if (key == KEY_W)
		vec2f_translate(&pl->pos,
			game->cam.dir.x * pl->speed * game->dtime, game->cam.dir.y * pl->speed * game->dtime);
	if (key == KEY_S)
		vec2f_translate(&pl->pos,
			-game->cam.dir.x * pl->speed * game->dtime, -game->cam.dir.y * pl->speed * game->dtime);
	if (key == KEY_A)
		vec2f_translate(&pl->pos,
			-game->cam.plane.x * pl->speed * game->dtime, -game->cam.plane.y * pl->speed * game->dtime);
	if (key == KEY_D)
		vec2f_translate(&pl->pos,
			game->cam.plane.x * pl->speed * game->dtime, game->cam.plane.y * pl->speed * game->dtime);
	if (key == KEY_LEFT)
		rotate(game, -game->cam.rotateSpeed * game->dtime);
	if (key == KEY_RIGHT)
		rotate(game, game->cam.rotateSpeed * game->dtime);
	if (key == KEY_ESC)
			mlx_loop_end(game->mlx);
}

void	keyboard_handle(t_game *const game)
{
	t_list *curr;

	curr = game->pressedKeys;
	while (curr)
	{
		key_handle(game, *((int *)curr->content));
		curr = curr->next;
	}
}
