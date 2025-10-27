/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:34:14 by phutran           #+#    #+#             */
/*   Updated: 2025/10/27 17:49:00 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	read_tiles(t_game *game, int fd)
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
		if (line[0] != '\n' && line[0] != '[')
		{
			elements = ft_split(line, " ");
			if (!elements)
				break ;
			if (elements[0][0] != '\n')
				validate_element(game, elements, &element_count);
			free(elements);
		}
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
	int32_t	j;

	new = NULL;
	j = 0;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line [0] == '[')
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
	if (ft_strcmp(fields[0], "WALL") == 0)
		parse_normal_wall_decoration(g, fields + 1);
	else if (ft_strcmp(fields[0], "DOOR") == 0)
		parse_door_decoration(g, fields + 1);
	else if (ft_strcmp(fields[0], "LIGHT") == 0)
		parse_light_decoration(g, fields + 1);
}

static void	read_decorations(t_game *g, int fd)
{
	char	*line;

	ft_get_next_line(fd);
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
			continue ;
		remove_nl(line);
		parse_decoration(g, line);
		free(line);
	}
}

static bool	line_is_whitespace(char *l)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		if (!ft_isspace(l[i]))
			return (false);
		++i;
	}
	return (true);
}

static void read_section_by_section(t_game *g, t_list **ls, int fd)
{
	char	*l;
	int32_t	sect_count;
	
	sect_count = 3;
	while (sect_count)
	{
		l = ft_get_next_line(fd);
		if (!l)
		{
			printf(".cub misses some configurations\n");
			exit(1);// ! HARDCODED EXIT
		}
		if (line_is_whitespace(l))
			continue ;
		if (ft_strcmp(l, "[TILES]\n") == 0)
			read_tiles(g, fd);
		else if (ft_strcmp(l, "[MAP]\n") == 0)
			read_map(g, ls, fd);
		else if (ft_strcmp(l, "[DECORATIONS]\n") == 0)
			read_decorations(g, fd);
		else
		{
			printf(".cub misses some configurations\n");
			exit(1);// ! HARDCODED EXIT
		}
		--sect_count;
	}
}

void	read_file(t_game *game, t_list **list, const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(ERROR_OPEN_FILE_FAILED, game);
	read_section_by_section(game, list, fd);
	close(fd);
	if (errno)
	{
		ft_lst_free(*list);
		exit_game(ERROR_READ_FILE_FAILED, game);
	}
}
