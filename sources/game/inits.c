/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:53:48 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 00:05:21 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_player	player_init(void)
{
	return ((t_player){
		.pos = vec2f_construct(5, 3), // ! POS IS HARDCODED
		.speed = 3.f,
		.base_speed = 3.f,
		.sprint_speed = 6.f,
		.radius = 6.f 
	});
}

#pragma region REMOVE WHEN PARSING IMPLEMENTED // !

#include <time.h>
char	**generate_map(int *w, int *h)
{
	#if 0
	const int HEIGHT = 6;
	const char *fixed_map[] = {
		"888888888884464464644464",
		"800000000084000000000004",
		"803300000884000000000006",
		"800300000000000000000006",
		"803300000884000000000004",
		"822222222222222222222226",
	};
	#else
	const int HEIGHT = 24;
	const int WIDTH = 25;
	const char *fixed_map[] = {
		"1111111141155<;=55555555",
		"100000000015000005000005",
		"101100000155000009000005",
		"1002000000D000000:000005",
		"101100000155000009000005",
		"10000000001500000555D555",
		"10000000001567855>>>0>>>",
		"1111D131111>?>?>>>00000>",
		">>>>0>>>>>>?00000>00000>",
		">0000000000A00000E00000>",
		">0000000000@00000>00000>",
		">0000000000>@>>@>>>>D>>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">0000000000000000000000>",
		">>>>>>>>>>>>>>>>>>>>>>>>"
	};
	#endif
	char **tiles;
	int y;

	tiles = malloc(sizeof(char *) * (HEIGHT + 1));
	if (!tiles)
		return NULL;

	for (y = 0; y < HEIGHT; y++)
	{
		tiles[y] = strdup(fixed_map[y]);
		if (!tiles[y])
		{
			while (--y >= 0)
				free(tiles[y]);
			free(tiles);
			return NULL;
		}
	}
	tiles[HEIGHT] = NULL;

	*w = WIDTH;
	*h = HEIGHT;
	return tiles;
}

t_map	init_map(const char *filename)
{
	t_map	res;

	(void)filename;
	res.tiles = generate_map(&res.size.x, &res.size.y);
	return (res);
}

t_input	init_input(void)
{
	t_input	res;

	ft_memset(&res, 0, sizeof (res));
	return (res);
}

t_cam	cam_init(void)
{
	return ((t_cam){
		.plane = vec2f_construct(0.66f, 0.f),
		.dir = vec2f_construct(0.f, 1.f),
		.sensitivity = 0.0008f,
		.pitch = 0,
		.bob_phase = 0
	});
}

#define CUBE(N, E, S, W) (t_cube){ .walls_ind = {N, E, S, W} }

//cube = {NORTH, WEST, SOUTH, EAST}

void	init_cubes(t_cube *cubes)
{
	int i = 0;
	cubes[i++] = CUBE(
		TEXTR_GRAY_BRICKWALL_NORTH,
		TEXTR_GRAY_BRICKWALL_EAST,
		TEXTR_GRAY_BRICKWALL_SHADOWED_SOUTH,
		TEXTR_GRAY_BRICKWALL_SHADOWED_WEST);
	cubes[i++] = CUBE(
		TEXTR_GRAY_BRICKWALL_NORTH,
		TEXTR_GRAY_BRICKWALL_EAST,
		TEXTR_GRAY_BRICKWALL_SHADOWED_SOUTH,
		TEXTR_NAZI_EAGLE_PICT_SHDWD);
	cubes[i++] = CUBE(
		TEXTR_HITLER_PICT,
		TEXTR_GRAY_BRICKWALL_EAST,
		TEXTR_GRAY_BRICKWALL_SHADOWED_SOUTH,
		TEXTR_GRAY_BRICKWALL_SHADOWED_WEST);
	cubes[i++] = CUBE(
		TEXTR_GRAY_BRICKWALL_NORTH,
		TEXTR_GRAY_BRICKWALL_EAST,
		TEXTR_HITLER_PICT_SHDWD,
		TEXTR_GRAY_BRICKWALL_SHADOWED_WEST);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_FLAG_NAZI,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_HITLER,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_FLAG_MILITARY,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_ARCHWAY,
		TEXTR_OFFICE_BEIGE_ARCHWAY,
		TEXTR_OFFICE_BEIGE_ARCHWAY,
		TEXTR_OFFICE_BEIGE_ARCHWAY);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_LAMP,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_LAMP);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_WINDOW_LARGE_CURTAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_LENIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN,
		TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_STALIN,
		TEXTR_OFFICE_BEIGE_WALL_PLAIN);
	cubes[i++] = CUBE(
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES);
	cubes[i++] = CUBE(
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES_BLOOD1,
		TEXTR_LAB_METAL_GREY_TILES_BLOOD1);
	cubes[i++] = CUBE(
		TEXTR_LAB_METAL_GREY_TILES_BLOOD2,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES_BLOOD2);
	cubes[i++] = CUBE(
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_GREY_TILES,
		TEXTR_LAB_METAL_SIGN_RADIATION);
}
