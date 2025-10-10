/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:59 by phutran           #+#    #+#             */
/*   Updated: 2025/10/10 17:51:44 by webxxcom         ###   ########.fr       */
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

static void	drawVertLine(t_game *const g, int screen_x, int line_h, float dist, t_txtres_sides side, t_vec2f rayDir)
{
	int	y_start;
	int	y_end;
	int	y;
	
	y_start = (g->h / 2) - (line_h / 2) + g->cam.pitch;
	if (y_start < 0)
		y_start = 0;
	y_end = (g->h / 2) + (line_h / 2) + g->cam.pitch;
	if (y_end >= g->h)
		y_end = g->h - 1;

	y = y_start;

	double wallX;
	if (side == EAST || side == WEST)
		wallX = g->player.pos.y + dist * rayDir.y;
	else
		wallX = g->player.pos.x + dist * rayDir.x;
	wallX -= floor(wallX);

	// uint64_t t = 0;
	// if (t == 0)
	// 	t = get_time_in_ms();
	// if (t - get_time_in_ms() > 1000)
	// 	printf("ASD");
	int texX = (int)(wallX * (double)g->cubes[0].walls[side]->width);
	if(side == WEST) texX = g->cubes[0].walls[side]->width - texX - 1;
    if(side == SOUTH) texX = g->cubes[0].walls[side]->width - texX - 1;
	double step = 1.0 * g->cubes[0].walls[side]->height / line_h;
	double texPos = (y_start - g->cam.pitch - g->h / 2.0 + line_h / 2.) * step;
	while (y < y_end)
	{
		int texY = (int)texPos % g->cubes[0].walls[side]->height;
        uint32_t color = im_get_pixel(g->cubes[0].walls[side], texX, texY);
		texPos += step;
		im_set_pixel(g->buffer_image, screen_x, y, color);
		y++;
	}
}

static void put_map(t_game *const game)
{
	int	screen_x;

	screen_x = 0;
	while (screen_x < game->w)
	{
		double cameraX = 2 * screen_x / (double)game->w - 1;
		t_vec2f rayDir = vec2f_construct(
			game->cam.dir.x + game->cam.plane.x * cameraX,
			game->cam.dir.y + game->cam.plane.y * cameraX);
		t_vec2f unitStep = vec2f_construct(fabs(1. / rayDir.x), fabs(1. / rayDir.y));
		t_vec2i mapStep;
		t_vec2f sideDist = init_startvals(game, rayDir, unitStep, &mapStep);
		t_vec2i mapPos = vec2i_construct(game->player.pos.x, game->player.pos.y);
		
		bool hit = false;
		float dist = 0;
		t_txtres_sides	side;
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				mapPos.x += mapStep.x;
				dist = sideDist.x;
				sideDist.x += unitStep.x;
				side = WEST;
			}
			else
			{
				mapPos.y += mapStep.y;
				dist = sideDist.y;
				sideDist.y += unitStep.y;
				side = NORTH;
			}
			if (game->map[mapPos.y][mapPos.x] != '0')
				hit = true;
		}
		if (rayDir.x < 0 && side == WEST)
			side = EAST;
		else if (rayDir.y < 0 && side == NORTH)
			side = SOUTH;
		drawVertLine(game, screen_x, game->h / dist, dist, side, rayDir);
		++screen_x;
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