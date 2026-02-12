/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:23:53 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	extract_pos(t_vec2i *pos, char *fields[])
{
	if (!pos_is_parseable(fields[0]) || !pos_is_parseable(fields[1]))
		return (error_found("Position is not parseable"));
	pos->x = ft_strtoi(fields[0], NULL);
	pos->y = ft_strtoi(fields[1], NULL);
	if (pos->x < 0 || pos->y < 0 || errno == ERANGE)
		return (error_found("Position must be in valid range"));
	return (0);
}

static int	extract_posf(char *fields[], t_vec2f *pos)
{
	pos->x = ft_atof(fields[0]);
	pos->y = ft_atof(fields[1]);
	if (pos->x < 0 || pos->y < 0)
		return (error_found(ERROR_NEG_POS));
	return (0);
}

int	parse_normal_wall_decoration(t_game *g, char *fields[])
{
	t_decoration	decor;

	if (!fields || !fields[0] || !fields[1] || !fields[2])
		return (error_found(ERROR_FEW_ATTRIBUTES_WALL));
	ft_memset(&decor, 0, sizeof(decor));
	if (extract_pos(&decor.pos, fields) || parse_direction(fields[3],
			&decor.direction))
		return (1);
	decor.texture_path = ft_strdup(fields[2]);
	if (!decor.texture_path)
		return (1);
	decor.type = DECOR_WALL;
	array_push(&g->map.decorations, &decor);
	return (0);
}

int	parse_door_decoration(t_game *g, char *fields[])
{
	t_decoration	decor;

	if (!fields || !fields[0] || !fields[1] || !fields[2])
		return (error_found(ERROR_FEW_ATTRIBUTES_DOOR));
	ft_memset(&decor, 0, sizeof(t_decoration));
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

	if (!fields || !fields[0] || !fields[1] || !fields[2])
		return (error_found(ERROR_FEW_ATTRIBUTES_SPRITE));
	ft_memset(&sprite, 0, sizeof(sprite));
	if (extract_posf(fields, &sprite.pos))
		return (1);
	sprite.texture_path = ft_strdup(fields[2]);
	if (!sprite.texture_path)
		return (1);
	sprite.type = SPRITE_STATIC;
	array_push(&g->sprites, &sprite);
	return (0);
}
