/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:53:48 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 11:56:25 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_player	player_init(void)
{
	return ((t_player){
		.pos = vec2f_construct(7, 3), // ! POS IS HARDCODED
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
	const int HEIGHT = 24;
	const char *fixed_map[] = {
		"888888888884464464644464",
		"800000000084000000000004",
		"803300000884000000000006",
		"800300000000000000000006",
		"803300000884000000000004",
		"800000000084000006660646",
		"888808888884444446000006",
		"777707777080808084040606",
		"770000007808080886000006",
		"700000000000000086000004",
		"700000000000000086060606",
		"770000007808080886460666",
		"777707777884068483330333",
		"222202222464006063000003",
		"220000022400000043000003",
		"200000002400000043000003",
		"100000001444446063300033",
		"200000002221222660050505",
		"220000022200022050500055",
		"200000002000002505050505",
		"100000000000000000000005",
		"200000002000002505050505",
		"220000022200022050500055",
		"222212222221222555555555"
	};
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

	*w = 28;
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
		.plane = vec2f_construct(0, 0.66f),
		.dir = vec2f_construct(-1, 0),
		.sensitivity = 0.0008f,
		.pitch = 0
	});
}