/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/31 14:23:28 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_txtres_sides	parse_direction(char *dir)
{
	if (ft_strcmp(dir, "SOUTH") == 0)
		return (SOUTH);
	if (ft_strcmp(dir, "EAST") == 0)
		return (EAST);
	if (ft_strcmp(dir, "WEST") == 0)
		return (WEST);
	if (ft_strcmp(dir, "NORTH") == 0)
		return (NORTH);
	printf("INCORRECT DECORATION DIRECTION %s\n", dir);
	exit(1); // NOTE if decoration direction is incorrect it's better to exit?
}

static t_vec2i	extract_pos(t_game *g, char *fields[])
{
	t_vec2i	pos;

	(void)g;
	pos = vec2i_construct(ft_atoi(fields[0]), ft_atoi(fields[1]));
	if (pos.x < 0 || pos.y < 0)
	{
		printf("ERRROR OUT OF BOUNDS WHILE PARSING POS (%d, %d)\n",
			pos.x, pos.y);
		exit(1);// HARDCODED EXIT
	}
	return (pos);
}

static t_vec2f	extract_posf(char *fields[])
{
	t_vec2f	pos;

	pos = vec2f_construct(ft_atof(fields[0]), ft_atof(fields[1]));
	if (pos.x < 0 || pos.y < 0)
	{
		printf("ERRROR OUT OF BOUNDS WHILE PARSING POS (%.2f, %.2f)\n",
			pos.x, pos.y); // NOTE revise for checking if position might be greater than map pos
		exit(1);// ! HARDCODED EXIT
	}
	return (pos);
}

void	parse_normal_wall_decoration(t_game *g, char *fields[])
{
	const t_vec2i	pos = extract_pos(g, fields);
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.pos = pos;
	decor.texture_path = ft_strdup(fields[2]);
	decor.direction = parse_direction(fields[3]);
	decor.type = DECOR_WALL;
	array_push(&g->map.decorations, &decor);
}

void	parse_door_decoration(t_game *g, char *fields[])
{
	const t_vec2i	pos = extract_pos(g, fields);
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.pos = pos;
	decor.texture_path = ft_strdup(fields[2]);
	decor.type = DECOR_DOOR;
	array_push(&g->map.decorations, &decor);
}

void	parse_sprite_decoration(t_game *g, char *fields[])
{
	t_sprite	sprite;

	ft_memset(&sprite, 0, sizeof (sprite));
	sprite.pos = extract_posf(fields);
	sprite.texture_path = ft_strdup(fields[2]);
	sprite.type = SPRITE_STATIC;
	array_push(&g->sprites, &sprite);
}

void	parse_light_decoration(t_game *g, char *fields[])
{
	const t_vec2i	pos = extract_pos(g, fields);
	t_decoration	decor;
	char			**colors;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.pos = pos;
	decor.texture_path = ft_strdup(fields[2]);
	decor.direction = parse_direction(fields[3]);
	decor.light.intensity = ft_atoi(fields[4]);
	decor.light.strength = ft_atoi(fields[5]);
	colors = ft_split(fields[6], ",");
	decor.light.color = colorf_from_uint(
			RGB(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])));
	ft_free_matrix(colors);
	decor.type = DECOR_LIGHT;
	array_push(&g->map.decorations, &decor);
}
