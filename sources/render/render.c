/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/09 12:13:55 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_vec2f	init_startvals(t_game *const game, const t_vec2f rayDir,
								const t_vec2f unitStep, t_vec2i *mapStep)
{
	t_vec2f	sideDist;

	sideDist = vec2f_init();
	if (rayDir.x < 0)
	{
		mapStep->x = -1;
		sideDist.x = (game->player.pos.x - (int)game->player.pos.x) * unitStep.x;
	}
	else
	{
		mapStep->x = 1;
		sideDist.x = ((int)game->player.pos.x + 1 - game->player.pos.x) * unitStep.x;
	}
	if (rayDir.y < 0)
	{
		mapStep->y = -1;
		sideDist.y = (game->player.pos.y - (int)game->player.pos.y) * unitStep.y;
	}
	else
	{
		mapStep->y = 1;
		sideDist.y = ((int)game->player.pos.y + 1 - game->player.pos.y) * unitStep.y;
	}
	return (sideDist);
}

static void	drawVertLine(t_game *const game, int x, int h, int col)
{
	int	y_start;
	int	y_end;
	int	y;
	
	y_start = (game->h / 2) - (h / 2);
	if (y_start < 0)
		y_start = 0;
	y_end = (game->h / 2) + (h / 2);
	if (y_end >= game->h)
		y_end = game->h - 1;

	y = y_start;
	while (y < y_end)
	{
		im_set_pixel(game->buffer_image, x, y, col);
		y++;
	}
}

static int getColor(int num)
{
	if (num == 1)
		return (0x808080); // grey wall
	else if (num == 2)
		return (0x0000FF); // blue tile
	else if (num == 3)
		return (0x00FF00); // green tile
	else if (num == 4)
		return (0xFF0000); // red tile
	else
		return (0xFFFFFF); // white fallback
}

static void put_map(t_game *const game)
{
	int	x;

	x = 0;
	while (x < game->w)
	{
		double cameraX = 2 * x / (double)game->w - 1;
		t_vec2f rayDir = vec2f_construct(
			game->cam.dir.x + game->cam.plane.x * cameraX,
			game->cam.dir.y + game->cam.plane.y * cameraX);
		t_vec2f unitStep = vec2f_construct(fabs(1. / rayDir.x), fabs(1. / rayDir.y));
		t_vec2i mapStep;
		t_vec2f sideDist = init_startvals(game, rayDir, unitStep, &mapStep);
		t_vec2i mapPos = vec2i_construct(game->player.pos.x, game->player.pos.y);
		
		bool hit = false;
		float dist = 0;
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				mapPos.x += mapStep.x;
				dist = sideDist.x;
				sideDist.x += unitStep.x;
			}
			else
			{
				mapPos.y += mapStep.y;
				dist = sideDist.y;
				sideDist.y += unitStep.y;
			}
			if (game->map[mapPos.y][mapPos.x] != '0')
				hit = true;
		}
		drawVertLine(game, x, game->h / dist, getColor(game->map[mapPos.y][mapPos.x] - '0'));
		++x;
	}
}

static void	put_buffer(t_game *const game)
{
	im_clear(game->buffer_image);
	put_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer_image->image, 0, 0);
}

void	game_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	put_buffer(game);
}