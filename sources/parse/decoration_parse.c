/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/26 13:34:37 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_txtres_sides	parse_direction(char *dir)
{
	if (ft_strncmp(dir, "SOUTH", 6) == 0)
		return (SOUTH);
	if (ft_strncmp(dir, "EAST", 5) == 0)
		return (EAST);
	if (ft_strncmp(dir, "WEST", 5) == 0)
		return (WEST);
	if (ft_strncmp(dir, "NORTH", 6) == 0)
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
		printf("ERRROR OUT OF BOUNDS WHILE PARSING POS (%d, %d)\n", pos.x, pos.y);
		exit(1);
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
	decor.texture_path = fields[2];
	decor.direction = parse_direction(fields[3]);
	array_push(&g->decorations, &decor);
}

void	parse_door_decoration(t_game *g, char *fields[])
{
	const t_vec2i	pos = extract_pos(g, fields);
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.pos = pos;
	decor.texture_path = fields[2];
	array_push(&g->decorations, &decor);
} 

void	parse_light_decoration(t_game *g, char *fields[])
{
	const t_vec2i	pos = extract_pos(g, fields);
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.pos = pos;
	decor.texture_path = fields[2];
	decor.direction = parse_direction(fields[3]);
	array_push(&g->decorations, &decor);
}