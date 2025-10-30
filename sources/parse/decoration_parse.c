/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/30 18:11:24 by phutran          ###   ########.fr       */
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
	exit(1);
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

// x	y	path	direction
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
