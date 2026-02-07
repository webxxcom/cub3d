/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/07 16:31:45 by webxxcom         ###   ########.fr       */
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

static bool		pos_is_parseable(char *field)
{
	while (ft_isspace(*field))
		++field;
	if (*field == '-' || *field == '+')
		++field;
	return (ft_isdigit(*field));
}

static int	extract_pos(t_vec2i *pos, char *fields[])
{
	if (!pos_is_parseable(fields[0]) || !pos_is_parseable(fields[1]))
		return error_found("Position is not parseable");
	pos->x = ft_strtoi(fields[0], NULL);
	pos->y = ft_strtoi(fields[1], NULL);
	if (pos->x < 0 || pos->y < 0 || errno == ERANGE)
		return (error_found("Position must be in valid range"));
	return (0);
}

t_vec2f	extract_posf(t_game *const g, char *fields[])
{
	t_vec2f	pos;

	pos = vec2f_construct(ft_atof(fields[0]), ft_atof(fields[1]));
	if (pos.x < 0 || pos.y < 0)
	{
		printf("ERRROR OUT OF BOUNDS WHILE PARSING POS (%.2f, %.2f)\n",
			pos.x, pos.y); // NOTE revise for checking if position might be greater than map pos
		exit_game("", g, NULL);
	}
	return (pos);
}

int	parse_normal_wall_decoration(t_game *g, char *fields[])
{
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (decor));
	extract_pos(&decor.pos, fields);
	decor.texture_path = ft_strdup(fields[2]);
	decor.direction = parse_direction(fields[3]);
	decor.type = DECOR_WALL;
	array_push(&g->map.decorations, &decor);
	return (0);
}

int	parse_door_decoration(t_game *g, char *fields[])
{
	t_decoration	decor;

	ft_memset(&decor, 0, sizeof (t_decoration));
	decor.type = DECOR_DOOR;
	if (extract_pos(&decor.pos, fields))
		return (1);
	decor.texture_path = ft_strdup(fields[2]);
	if (!decor.texture_path)
		return (1);
	array_push(&g->map.decorations, &decor);
	return (0);
}

int	parse_sprite_decoration(t_game *g, char *fields[])
{
	t_sprite	sprite;

	ft_memset(&sprite, 0, sizeof (sprite));
	sprite.pos = extract_posf(g, fields);
	sprite.texture_path = ft_strdup(fields[2]);
	sprite.type = SPRITE_STATIC;
	array_push(&g->sprites, &sprite);
	return (0);
}


