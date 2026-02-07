/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/07 12:14:53 by webxxcom         ###   ########.fr       */
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
		return error_found("The position is not parseable");
	pos->x = ft_atoi(fields[0]);
	pos->y = ft_atoi(fields[1]);
	if (pos->x < 0 || pos->y < 0)
	{
		printf("The position for decoration is out of bounds (%d, %d)\n",
			pos->x, pos->y);
		return (1);
	}
	return (0);
}

static t_vec2f	extract_posf(t_game *const g, char *fields[])
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

int	parse_light_decoration(t_game *g, char *fields[])
{
	const t_vec2f	pos = extract_posf(g, fields);
	t_light			light;
	char			**colors;

	ft_memset(&light, 0, sizeof (light));
	light.pos = pos;
	light.intensity = ft_atoi(fields[2]);
	light.strength = ft_atoi(fields[3]);
	colors = ft_split(fields[4], ",");
	if (!colors[0] || !colors[1] || !colors[2])
	{
		ft_printf("Misconfiguration for light parsing has been found\n"
			"	The color values are not correct\n");
		ft_free_matrix(colors);
		return 1;
	}
	light.color = colorf_from_uint(
		RGB(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])));
	ft_free_matrix(colors);
	array_push(&g->lights, &light);
	return (0);
}
