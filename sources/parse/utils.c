/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:05:45 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 16:41:12 by phutran          ###   ########.fr       */
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

void	parse_decoration(t_game *g, char *line)
{
	char	**fields;

	fields = ft_split(line, " \t");
	if (!ft_strcmp(fields[0], "WALL"))
		parse_normal_wall_decoration(g, fields + 1);
	else if (!ft_strcmp(fields[0], "DOOR"))
		parse_door_decoration(g, fields + 1);
	else if (!ft_strcmp(fields[0], "LIGHT"))
		parse_light_decoration(g, fields + 1);
	ft_free_matrix(fields);
}

void	read_decorations(t_game *g, int fd)
{
	char	*line;

	free(ft_get_next_line(fd));
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (!line_is_whitespace(line))
		{
			remove_nl(line);
			parse_decoration(g, line);
		}
		free(line);
	}
}

void	set_player_start_pos(t_game *g, int x, int y, char dir)
{
	g->player.pos = (t_vec2f){.x = x, .y = y};
	if (dir == 'N')
	{
		g->cam.dir = vec2f_construct(0, -1);
		g->cam.plane = vec2f_construct(0.66, 0);
	}
	else if (dir == 'W')
	{
		g->cam.dir = vec2f_construct(-1, 0);
		g->cam.plane = vec2f_construct(0, -0.66);
	}
	else if (dir == 'S')
	{
		g->cam.dir = vec2f_construct(0, 1);
		g->cam.plane = vec2f_construct(-0.66, 0);
	}
	else
	{
		g->cam.dir = vec2f_construct(1, 0);
		g->cam.plane = vec2f_construct(0, 0.66);
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
