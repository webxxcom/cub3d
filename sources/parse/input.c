/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:34:14 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 13:25:40 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	read_textures(t_game *game, int fd)
{
	char	*line;
	char	**elements;
	int		element_count;

	element_count = 6;
	while (element_count)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		elements = ft_split(line, " ");
		if (!elements)
			break ;
		if (elements[0][0] != '\n')
			validate_element(game, elements, &element_count);
		free(elements);
		free(line);
	}
	if (element_count)
	{
		close(fd);
		exit_game(ERROR_MISSING_TEXTURE, game);
	}
}

static void	set_player_start_pos(t_game *g, int x, int y, char dir)
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

static void	find_and_set_player_pos(t_game *g, char *l, int j)
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

static void	read_map(t_game *game, t_list **list, int fd)
{
	t_list	*new;
	char	*line;
	int		j;

	new = NULL;
	j = 0;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			if (!new)
				continue ;
			else
				break ;
		}
		find_and_set_player_pos(game, line, j++);
		new = ft_lstnew(line);
		if (!new)
			break ;
		ft_lstadd_back(list, new);
	}
}

static void	parse_decoration(t_game *g, char *line)
{
	char			**fields;

	fields = ft_split(line, " \t");
	if (ft_strncmp(fields[0], "WALL", 5) == 0)
		parse_normal_wall_decoration(g, fields + 1);
	else if (ft_strncmp(fields[0], "DOOR", 5) == 0)
		parse_door_decoration(g, fields + 1);
	else if (ft_strncmp(fields[0], "LIGHT", 6) == 0)
		parse_light_decoration(g, fields + 1);
}

static void	read_decorations(t_game *g, int fd)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '#')
			continue ;
		remove_nl(line);
		parse_decoration(g, line);
		free(line);
	}
	// if (errno)
	// {
	// 	close(fd);
	// 	exit_game(ERROR_READ_FILE_FAILED, g);
	// }
}

void	read_file(t_game *game, t_list **list, const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(ERROR_OPEN_FILE_FAILED, game);
	read_textures(game, fd);
	read_map(game, list, fd);
	read_decorations(game, fd);
	close(fd);
	if (errno)
	{
		ft_lst_free(*list);
		exit_game(ERROR_READ_FILE_FAILED, game);
	}
}
