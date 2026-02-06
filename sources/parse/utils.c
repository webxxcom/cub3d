/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:05:45 by phutran           #+#    #+#             */
/*   Updated: 2026/02/06 18:23:14 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**get_chars_map(t_map *map)
{
	char	**map_chars;
	int32_t	i;
	int32_t	j;

	map_chars = ft_calloc(map->size.y + 1, sizeof (char *));
	j = 0;
	while (j < map->size.y)
	{
		map_chars[j] = ft_calloc(map->size.x, sizeof (char));
		i = 0;
		while (i < map->size.x)
		{
			map_chars[j][i] = map->tiles[j][i].type;
			++i;
		}
		++j;
	}
	map_chars[j] = NULL;
	return (map_chars);
}

int	parse_decoration(t_game *g, char *line)
{
	char	**fields;
	int		res;

	res = 0;
	if (*line != '#')
	{
		fields = ft_split(line, " \t");
		if (fields)
		{
			if (!ft_strcmp(fields[0], "WALL"))
				res = parse_normal_wall_decoration(g, fields + 1);
			else if (!ft_strcmp(fields[0], "DOOR"))
				res = parse_door_decoration(g, fields + 1);
			else if (!ft_strcmp(fields[0], "LIGHT"))
				res = parse_light_decoration(g, fields + 1);
			else if (!ft_strcmp(fields[0], "SPRITE"))
				res = parse_sprite_decoration(g, fields + 1);
			ft_free_matrix(fields);
		}
		else
			ft_printf("INFO: The line %s for decoration was not parsed due to unexpected error\n", line);
	}
	return (res);
}

int	read_decorations(t_game *g, int fd)
{
	int		res;
	char	*l;

	l = ft_get_next_line(fd);
	if (l)
		free(l);
	res = 0;
	while (1)
	{
		l = ft_get_next_line(fd);
		if (!l)
			break ;
		if (!line_is_whitespace(l))
			res = parse_decoration(g, remove_nl(l));
		freenull(&l);
	}
	return (res);
}

void	set_player_start_pos(t_game *g, int x, int y, char dir)
{
	g->player.pos = (t_vec2f){.x = x + 0.5f, .y = y + 0.5f};
	if (dir == 'N')
	{
		g->player.dir = vec2f_construct(0, -1);
		g->player.plane = vec2f_construct(CAMERA_FOV, 0);
	}
	else if (dir == 'W')
	{
		g->player.dir = vec2f_construct(-1, 0);
		g->player.plane = vec2f_construct(0, -CAMERA_FOV);
	}
	else if (dir == 'S')
	{
		g->player.dir = vec2f_construct(0, 1);
		g->player.plane = vec2f_construct(-CAMERA_FOV, 0);
	}
	else
	{
		g->player.dir = vec2f_construct(1, 0);
		g->player.plane = vec2f_construct(0, CAMERA_FOV);
	}
}

void	find_and_set_player_pos(t_game *g, char *l, int j)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'E' || l[i] == 'W')
		{
			set_player_start_pos(g, i, j, l[i]);
			return ;
		}
		++i;
	}
}
